package org.example;

import javax.lang.model.element.ModuleElement;
import java.util.ArrayList;
import java.util.List;
import java.util.Optional;

public class Graph {
    private final List<Vertex> vertices;
    private final List<Edge> edges;
    private boolean isDirected;

    public Graph(){
        this(false);
    }

    public Graph(boolean isDirected) {
        this.isDirected = isDirected;
        vertices = new ArrayList<>();
        edges = new ArrayList<>();
    }

    public void addVertices(String... verticesNames){
        for(String vName : verticesNames){
            vertices.add(new Vertex(vName));
        }
    }

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

        inferDirectedness(v1, v2);
        edges.add(new Edge(edgeName, v1, v2));
    }

    public void inferDirectedness(Vertex v1, Vertex v2){
        if(!isDirected){
            if(isSelfLoop(v1, v2)){
                isDirected = true;
            }else{
                for(Edge edge : edges){
                    if(isSameDirectionEdge(v1, v2, edge)){
                        isDirected = true;
                        break;
                    }else if(isReverseEdge(v1, v2, edge)){
                        isDirected = true;
                        break;
                    }
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
        for (Vertex vertex : vertices) {
            if (vertex.getName().equalsIgnoreCase(vName)) {
                return Optional.of(vertex);
            }
        }
        return Optional.empty();
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
        sb.append("***Graph***\n");
        sb.append("***Vertices:\n");
        for (Vertex v : vertices) {
            sb.append("\t").append(v.getName()).append("\n");
        }
        sb.append("Total number of vertices: ").append(getNumberOfVertices());
        sb.append("***Edges:\n");
        for (Edge e : edges) {
            sb.append("\t").append(e.getName()).append(": ").append(e.getVertexSource().getName())
                    .append(" - ").append(e.getVertexDestination().getName()).append("\n");
        }
        sb.append("Total number of edges: ").append(getNumberOfEdges());
        return sb.toString();
    }
}