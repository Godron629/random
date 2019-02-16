import os

import geopy
import networkx as nx
import osmnx as ox


GRAPH_FILE = 'lethbridge_graph_all.graphml'
GRAPH_FOLDER = os.path.dirname(os.path.realpath(__file__))


def maximum_indegree(local=True):
    '''
    Find the intersection within the City of Lethbridge
    with the most roads heading into that intersection.
    I.e. the max indegree of a graph

    :param bool local: if True, load City of Lethbridge
        graph from local source, else, online.

    :return None:
    '''
    if local:
        # Load City of Lethbridge map from file, to save time
        city_graph = ox.load_graphml(GRAPH_FILE, GRAPH_FOLDER)
    else:
        place_name = 'City of Lethbridge, Alberta'
        city_graph = ox.graph_from_place(place_name, network_type='all')

    # Compute the indegree of each intersection (node)
    all_node_indegrees = nx.in_degree_centrality(city_graph)

    # Find intersection with the highest indegree value
    max_indegree = max(all_node_indegrees.items(), key=lambda x: x[1])
    max_indegree_node = city_graph.nodes.get(max_indegree[0])

    # Find readable address of that intersection
    geolocator = load_geopy_geolocator('Nominatim')
    intersection_location = geolocator.reverse((
        max_indegree_node['y'],
        max_indegree_node['x']))

    # Load graph from intersection address
    intersection_graph = ox.graph_from_address(
        intersection_location.address,
        network_type='all',
        distance=500)

    # Hide all nodes except for intersection
    node_colors = color_single_node(
        intersection_graph.nodes,
        max_indegree_node['osmid'])

    # Display intersection and surrounding paths
    ox.plot_graph(intersection_graph, node_color=node_colors, node_size=60)

    # Output other results
    print(format_output(max_indegree_node, intersection_location))

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

def color_single_node(nodes, node_id):
    '''
    Return list of colors where every color except for
    `node_id` is invisable.

    :param list nodes:
    :param int node_id:

    :return list:
    '''
    # 'r' as in red, 'w' as in white
    return ['r' if node == node_id else 'w' for node in nodes]

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
    maximum_indegree()
