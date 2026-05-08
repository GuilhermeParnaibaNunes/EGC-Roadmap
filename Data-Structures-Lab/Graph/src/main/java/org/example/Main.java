package org.example;

public class Main {
    public static void main(String[] args){
        Graph graph = new Graph(); //not directed
        graph.addVertices("1", "7", "3", "4", "5", "6");
        graph.addEdges("1", "3");
        graph.addEdges("1", "4");
        graph.addEdges("1", "5");
        graph.addEdges("7", "3");
        graph.addEdges("7", "4");
        graph.addEdges("7", "5");
        graph.addEdges("3", "5");
        graph.addEdges("4", "5");
        graph.addEdges("6", "6");

        System.out.println(graph);
    }
}