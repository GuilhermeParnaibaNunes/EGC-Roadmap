package org.example;

import java.util.ArrayList;
import java.util.List;
import java.util.Optional;

public class Graph {
    private final List<Vertex> vertices;
    private final List<Edge> edges;
    private boolean isDirected;
    private final List<List<Vertex>> inAdjacencyList; // Lista de Adjacentes
    private final List<List<Vertex>> outAdjacencyList; // Lista de Adjacências

    public Graph(){
        this(false);
    }

    public Graph(boolean isDirected) {
        this.isDirected = isDirected;
        vertices = new ArrayList<>();
        edges = new ArrayList<>();
        inAdjacencyList = new ArrayList<>();
        outAdjacencyList = new ArrayList<>();
    }

    public void addVertices(String... verticesNames){
        for(String vName : verticesNames){
            Vertex newV = new Vertex(vName);
            vertices.add(newV);

            createVerticesAdjacencyLists(newV);
        }
    }

    private void createVerticesAdjacencyLists(Vertex vertex){
        List<Vertex> inVList = new ArrayList<>();
        inVList.add(vertex);
        List<Vertex> outVList = new ArrayList<>();
        outVList.add(vertex);
        inAdjacencyList.add(inVList);
        outAdjacencyList.add(outVList);
    }

    //TODO: It feels unnecessary to have two versions of addEdges
    public void addEdges(String sourceVName, String destinationVName){
        createEdge("", sourceVName, destinationVName);
    }

    public void addEdges(String edgeName, String sourceVName, String destinationVName){
        createEdge(edgeName, sourceVName, destinationVName);
    }

    public void createEdge(String edgeName, String v1Name, String v2Name){
        Vertex v1 = searchVertex(v1Name)
                .orElseThrow(() -> new IllegalArgumentException("Vertex " + v1Name + " not found."));

        Vertex v2 = searchVertex(v2Name)
                .orElseThrow(() -> new IllegalArgumentException("Vertex " + v2Name + " not found."));

        if(!isDirected)
            inferDirectedness(v1, v2);
        handleAdjacency(v1, v2);
        edges.add(new Edge(edgeName, v1, v2));
    }

    public void inferDirectedness(Vertex v1, Vertex v2){
        if(isSelfLoop(v1, v2)){
            isDirected = true;
            redoDirectedAdjacencyLists();
        }else{
            for(Edge edge : edges){
                if(isSameDirectionEdge(v1, v2, edge)){
                    isDirected = true;
                    redoDirectedAdjacencyLists();
                    break;
                }else if(isReverseEdge(v1, v2, edge)){
                    isDirected = true;
                    redoDirectedAdjacencyLists();
                    break;
                }
            }
        }
    }

    public static boolean isSelfLoop(Vertex v1, Vertex v2){
        return v1.getName().equals(v2.getName());
    }

    public static boolean isSameDirectionEdge(Vertex v1,Vertex v2,Edge edge){
        return v1.equals(edge.getVertexSource()) && v2.equals(edge.getVertexDestination());
    }

    public static boolean isReverseEdge(Vertex v1,Vertex v2,Edge edge){
        return v2.equals(edge.getVertexSource()) && v1.equals(edge.getVertexDestination());
    }

    public Optional<Vertex> searchVertex(String vName){
        for(Vertex vertex : vertices) {
            if(vertex.getName().equalsIgnoreCase(vName)) {
                return Optional.of(vertex);
            }
        }
        return Optional.empty();
    }

    public Optional<List<Vertex>> searchInVertex(String vName){
        for(List<Vertex> vertexList : inAdjacencyList) {
            if(vertexList.getFirst().getName().equalsIgnoreCase(vName)) {
                return Optional.of(vertexList);
            }
        }
        return Optional.empty();
    }

    //TODO: DUPLICATED CODE, MAY FIND A WAY TO PASS xAdjacencyList as an argument to inner function
    public Optional<List<Vertex>> searchOutVertex(String vName){
        for (List<Vertex> vertexList : outAdjacencyList) {
            if (vertexList.getFirst().getName().equalsIgnoreCase(vName)) {
                return Optional.of(vertexList);
            }
        }
        return Optional.empty();
    }

    private void redoDirectedAdjacencyLists(){
        resetAdjacencyLists();
        for(Edge edge : edges){
            handleAdjacency(edge.getVertexSource(), edge.getVertexDestination());
        }
    }

    private void resetAdjacencyLists(){
        inAdjacencyList.clear();
        outAdjacencyList.clear();

        for(Vertex vertex : vertices){
            createVerticesAdjacencyLists(vertex);
        }
    }

    public void handleAdjacency(Vertex vSource, Vertex vDestination){
        handleInAdjacency(vSource, vDestination);
        handleOutAdjacency(vSource, vDestination);
    }

    private void handleInAdjacency(Vertex v1, Vertex v2){
        List<Vertex> v2InAdjacencyList = searchInVertex(v2.getName())
                .orElseThrow(() -> new IllegalArgumentException("Vertex " + v2.getName() + "in adjacency list not found."));

        v2InAdjacencyList.add(v1);

        if(!isDirected){
            List<Vertex> v1InAdjacencyList = searchInVertex(v1.getName())
                    .orElseThrow(() -> new IllegalArgumentException("Vertex " + v1.getName() + "in adjacency list not found."));

            v1InAdjacencyList.add(v2);
        }
    }

    private void handleOutAdjacency(Vertex v1, Vertex v2){
        List<Vertex> v1OutAdjacencyList = searchOutVertex(v1.getName())
                .orElseThrow(() -> new IllegalArgumentException("Vertex " + v1.getName() + "in adjacency list not found."));

        v1OutAdjacencyList.add(v2);

        if(!isDirected){
            List<Vertex> v2OutAdjacencyList = searchOutVertex(v2.getName())
                    .orElseThrow(() -> new IllegalArgumentException("Vertex " + v2.getName() + "in adjacency list not found."));

            v2OutAdjacencyList.add(v1);
        }
    }

    public int getNumberOfVertices(){ //ORDEM
        return vertices.size();
    }

    public int getNumberOfEdges(){ //TAMANHO
        return edges.size();
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        sb.append("***Graph***\n\n");
        sb.append("***Is directed? ").append(isDirected).append("\n\n");
        sb.append("***Vertices:\n");
        for (Vertex v : vertices) {
            sb.append("\t - ").append(v.getName()).append("\n");
        }
        sb.append("Total number of vertices: ").append(getNumberOfVertices());
        sb.append("\n\n***Edges:\n");
        for (Edge e : edges) {
            sb.append("\t - ").append(e.getName()).append(": ").append(e.getVertexSource().getName())
                    .append(" - ").append(e.getVertexDestination().getName()).append("\n");
        }
        sb.append("Total number of edges: ").append(getNumberOfEdges());
        sb.append("\n\n***Adjacency List: ");
        for (List<Vertex> outVList : outAdjacencyList) {
            sb.append("\n\t - ").append(outVList.getFirst().getName());
            for (int i = 1; i < outVList.size(); i++) {
                sb.append(" -> [").append(outVList.get(i).getName()).append("]");
            }
        }
        return sb.toString();
    }
}