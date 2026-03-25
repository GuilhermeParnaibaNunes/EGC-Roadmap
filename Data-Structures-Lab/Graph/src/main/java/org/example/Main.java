package org.example;

public class Main {
    public static void main(String[] args){
        Graph graph = new Graph();

        //Vertex v1 = new Vertex("Vertex 1");
        //Vertex v2 = new Vertex("Vertex 2");
        //Edge e1 = new Edge(v1, v2, "Edge 1");
        //graph.addVertex(v1);
        //graph.addVertex(v2);

        // List<Vertex> vertices = new ArrayList<>();
        // List<Edge> edges = new ArrayList<>();

        // for(int i = 0; i < 5; i++) {
        //     vertices.add(new Vertex("Vertex " + (i + 1)));
        // }

        // for(int i = 0; i < vertices.size() - 1; i++) {
        //     edges.add(new Edge(vertices.get(i), vertices.get(i + 1), "Edge " + (i + 1)));
        // }

        // Graph graph = new Graph(vertices, edges);

        System.out.println(graph.toString());
    }
}