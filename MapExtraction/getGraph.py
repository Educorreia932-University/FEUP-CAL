import osmnx as ox
import networkx as nx
import pandas as pd


def cleanData(df):
    df.drop(["geometry", "ref", "tunnel", "bridge", "lanes", "highway", "width", "junction", "access", "service"],
            axis=1, inplace=True)
    df['maxspeed'] = df['maxspeed'].fillna(0)
    df['name'] = df['name'].fillna("NONE")
    print(df.isnull().sum())
    print(df.columns)
    return df


def getNodes(graph):
    return pd.DataFrame(list(graph.nodes))


def getEdges(graph):
    return nx.to_pandas_edgelist(graph)


# It saves the data in csv by node and edges
def saveData(graph):
    edges = getEdges(graph)
    edges = cleanData(edges)
    edges.to_csv('edges.csv', index=False, encoding="latin1")
    getNodes(graph).to_csv('nodes.csv', index=False)


def main(cityName, placeName):
    ox.config(log_console=True, use_cache=True)
    graph = ox.core.graph_from_place(placeName, network_type='drive')
    ox.plot_graph(graph, save=True, filename=cityName, file_format="png")
    ox.extended_stats(graph, ecc=True)
    saveData(graph)


main("Porto", "Município do Porto, Portugal")
