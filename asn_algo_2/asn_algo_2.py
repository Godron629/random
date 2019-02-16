"""
Gideon Richter
001181085
CPSC 4110: Algorithms Project Assignment 2
"""
import os
import pickle
from datetime import datetime

import geopy
import networkx as nx
from networkx.exception import NetworkXNoPath
import osmnx as ox

LETHBRIDGE = 'City of Lethbridge, Alberta'
LETHBRIDGE_GRAPH = 'lethbridge_graph_drive.graphml'
LETHBRIDGE_SHORTEST_PATH = 'lethbridge_shortest_path.pickle'

COCHRANE = 'Town of Cochrane, Alberta'
COCHRANE_GRAPH = 'cochrane_graph_all.graphml'
COCHRANE_SHORTEST_PATH = 'cochrane_shortest_path.pickle'

GRAPH_FOLDER = os.path.dirname(os.path.realpath(__file__))


def p_center(p, city_graph, shortest_path_pickle=None):
    
    all_node_keys = list(city_graph._node.keys())
    
    all_pairs_shortest_path = get_all_pairs_shortest_path(
        city_graph,
        all_node_keys,
        shortest_path_pickle,
    )
    
    # Get the maximum length to each node
    all_pairs_path_maximums = {
        k: max(v.values()) for k, v in 
        all_pairs_shortest_path.items()
    }
    
    # Get rid of 0 length paths
    all_node_keys = [x for x in all_node_keys if all_pairs_path_maximums[x] != 0]
    all_pairs_shortest_path = {k:v for k,v in all_pairs_shortest_path.items() if v != 0}
    
    # Assign the first 'p' nodes to be our solution
    centers = all_node_keys[:p]
    
    # Compute the total cost for each center in `centers`
    center_costs = {k: all_pairs_path_maximums[k] for k in centers}
    
    centers, center_costs = find_p_centers(
        centers,
        all_node_keys,
        all_pairs_path_maximums,
        center_costs
    )
                
    node_information = {}
    for center in centers: 
        node = city_graph._node[center]
        # Find readable address of that node
        geolocator = load_geopy_geolocator('Nominatim')
        location = geolocator.reverse((
            node['y'],
            node['x']))
        
        node_information[center] = {
            'address': location.address,
            'id': center,
            'lat': location.latitude,
            'lon': location.longitude,
        }
        
    total_cost = sum(center_costs.values())
        
    return total_cost, node_information

def p_median(p, city_graph, shortest_path_pickle=None):
    
    all_node_keys = list(city_graph._node.keys())
    
    all_pairs_shortest_path = get_all_pairs_shortest_path(
        city_graph,
        all_node_keys,
        shortest_path_pickle,
    )
    
    # Sum lengths from nodes to every other node
    all_pairs_path_sums = {
        k: sum(v.values()) for k, v in 
        all_pairs_shortest_path.items()
    }
    
    # Get rid of 0 length paths
    all_node_keys = [x for x in all_node_keys if all_pairs_path_sums[x] != 0]
    all_pairs_shortest_path = {k:v for k,v in all_pairs_shortest_path.items() if v != 0}
    
    # Assign the first 'p' nodes to be our solution
    medians = all_node_keys[:p]
    
    # Compute the total cost for each median in `medians`
    median_costs = {k: all_pairs_path_sums[k] for k in medians}
    
    medians, median_costs = find_p_medians(
        medians,
        all_node_keys,
        all_pairs_path_sums,
        median_costs
    )
                
    node_information = {}
    for median in medians: 
        node = city_graph._node[median]
        # Find readable address of that node
        geolocator = load_geopy_geolocator('Nominatim')
        location = geolocator.reverse((
            node['y'],
            node['x']))
        
        node_information[median] = {
            'address': location.address,
            'id': median,
            'lat': location.latitude,
            'lon': location.longitude,
        }
        
    total_cost = sum(median_costs.values())
        
    return total_cost, node_information
        

def find_p_medians(medians, all_node_keys, all_pairs_path_sums, median_costs) -> tuple:
    """
    Use local search algorithm described here: http://mauricio.resende.info/talks/pmedianls.pdf
    to find optimal p-medians. Start with a solution (we have picked a solution to be the 
    first p-nodes of the graph), and for each median, replace it with a node in the graph 
    that is not already part of the solution. If the total cost is lower than before, 
    use that node instead of the original one. Do this until there are no node swaps.
    
    :param list medians: 
    :param list all_node_keys: 
    :param dict all_pairs_path_sums: 
    :param dict median_costs: 
    """
    while True:
        restart = False
        for i, median in enumerate(medians): 
            if restart: 
                # We redefined `medians`, so re-enter that loop 
                break
            for j, potential_median in enumerate(all_node_keys):
                potential_median_cost = all_pairs_path_sums[potential_median]
                if potential_median not in median_costs: 
                    # Replace `center` in center_costs with `potential_median`
                    center_costs_without_i = {k:v for k,v in median_costs.items() if k != median}
                    center_costs_without_i[potential_median] = potential_median_cost
                    if (sum(center_costs_without_i.values()) < sum(median_costs.values()) and
                        sum(center_costs_without_i.values()) != 0):
                        # If we're better off with `potential_median`, then use it instead
                        median_costs.pop(median, None)
                        median_costs[potential_median] = all_pairs_path_sums[potential_median]
                        # Reassign `medians` and restart the while loop
                        medians = [x for x in median_costs]
                        restart = True
                        break # out of the For loop
        if not restart: 
            # This happens if we've iterated all nodes 
            # and none of them improved the solution.
            return medians, median_costs 
        
def find_p_centers(centers, all_node_keys, all_pairs_path_max, center_costs) -> tuple: 
    """
    Use local search algorithm described here: http://mauricio.resende.info/talks/pmedianls.pdf
    to find optimal p-centers. Start with a solution (we have picked a solution to be the 
    first p-nodes of the graph), and for each center, replace it with a node in the graph 
    that is not already part of the solution. If the maximum distance is lower than before, 
    use that node instead of the original one. Do this until there are no node swaps.
    
    :param list centers: 
    :param list all_node_keys: 
    :param all_pairs_path_max: 
    :param center_costs: 
    """
    while True:
        restart = False
        for i, center in enumerate(centers): 
            if restart: 
                # We redefined `centers`, so re-enter that loop 
                break
            for j, potential_center in enumerate(all_node_keys):
                potential_center_distance = all_pairs_path_max[potential_center]
                if potential_center not in center_costs: 
                    # Replace `center` in center_costs with `potential_center`
                    center_costs_without_i = {k:v for k,v in center_costs.items() if k != center}
                    center_costs_without_i[potential_center] = potential_center_distance
                    if sum(center_costs_without_i.values()) < sum(center_costs.values()):
                        # If we're better off with `potential_center`, then use it instead
                        center_costs.pop(center, None)
                        center_costs[potential_center] = all_pairs_path_max[potential_center]
                        # Reassign centers and restart the while loop
                        medians = [x for x in center_costs]
                        restart = True
                        break # out of the For loop
        if not restart: 
            # This happens if we've iterated all nodes 
            # and none of them improved the solution.
            return centers, center_costs 

def get_all_pairs_shortest_path(graph, all_node_keys, shortest_path_pickle) -> dict:
    """
    Load or compute all_pairs_shortest_path for a graph. These are 
    the length of the path from every node to every other node. 
    
    :param nx.Graph graph: 
    :param list all_node_keys: node keys of `graph`
    :param str shortest_path_pickle: 
    """
    if shortest_path_pickle: 
        # Load the file instead of calculating all_pairs_shortest_path each time
        all_pairs_shortest_path = pickle.load(open(shortest_path_pickle, 'rb'))
    else:
        all_pairs_shortest_path = {}
        for i, node in enumerate(all_node_keys): 
            print('{}/{}'.format(i, len(all_node_keys)))
            # Compute the length of paths from node to every other node
            all_pairs_shortest_path[node] = nx.shortest_path_length(graph, source=node)
            
    return all_pairs_shortest_path

def load_geopy_geolocator(service):
    '''
    Set up and return a geopy geocoder object

    :param str service: name of service corresponding to
        geocoder

    :return geopy.Geocoder:
    '''
    agent_name = 'asn1/gideon.richter@uleth.ca'
    geopy.geocoders.options.default_user_agent = agent_name
    geopy.geocoders.options.default_timeout = 10
    locator_cls = geopy.get_geocoder_for_service(service)
    return locator_cls()

def color_nodes(nodes, node_ids):
    '''
    Return list of colors where every color except for
    `node_ids` is invisible.

    :param list nodes:
    :param list node_ids:

    :return list:
    '''
    # 'r' as in red, 'w' as in white
    return ['r' if node in node_ids else 'w' for node in nodes]

def format_output(node, location):
    '''
    Form a string with the assignment output

    :param OSMnx.node node:
    :param str location: location of node

    :return str:
    '''
    return (
        'Output:'
        '\n  Node ID: {}'
        '\n  Lat: {}'
        '\n  Lon: {}'
        '\n  Address: {}'
        '\n\n  By: Gideon Richter'
        .format(node['osmid'], node['y'], node['x'], location.address))


if __name__ == '__main__':
    
    city = 'City of Calgary, Alberta'
    #city = 'City of Lethbridge, Alberta'
    #city = 'City of Edmonton, Alberta'
    
    cities = {
        'cochrane': {
            'graph_file': COCHRANE_GRAPH,
            'shortest_path': COCHRANE_SHORTEST_PATH
        },
        'lethbridge': {
            'graph_file': LETHBRIDGE_GRAPH,
            'shortest_path': LETHBRIDGE_SHORTEST_PATH
        }
    }
    
    city_to_use = 'lethbridge'
    #city_to_use = 'cochrane'
    
    city_info = cities[city_to_use]
    
    # Load City of Lethbridge map from file, to save time
    city_graph = ox.load_graphml(city_info['graph_file'], GRAPH_FOLDER)
    shortest_path_file = city_info['shortest_path']
    
    """
    city_graph = ox.graph_from_place(
        'Town of Cochrane, Alberta',
        network_type='drive',
        simplify=True,
        clean_periphery=True,
        truncate_by_edge=True
    )
    """
    
    p = 2

    before = datetime.utcnow()
    median_result_costs, median_result_nodes = \
        p_median(p, city_graph, shortest_path_pickle=shortest_path_file)    
    print('median time: {}'.format(datetime.utcnow() - before))
    
    before = datetime.utcnow()
    center_result_costs, center_result_nodes = \
        p_center(p, city_graph, shortest_path_pickle=shortest_path_file)            
    print('center time: {}'.format(datetime.utcnow() - before))