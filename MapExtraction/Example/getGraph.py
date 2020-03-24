import osmnx as ox 

ox.utils.config(all_oneway=True) 
graph = ox.graph_from_place('Piedmont, California, USA', network_type = 'drive')
#fig, ax = ox.plot_graph(graph)

ox.save_load.save_graph_shapefile(graph, "nodes_test")