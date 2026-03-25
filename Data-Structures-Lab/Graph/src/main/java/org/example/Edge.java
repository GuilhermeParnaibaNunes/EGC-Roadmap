package org.example;

public class Edge {
    private Vertex source;
    private Vertex destination;
    private String name;

    public Edge(String name, Vertex source, Vertex destination){
        setVertexSource(source);
        setVertexDestination(destination);
        setName(name);
    }

    public void setName(String name) {
        if(name != null && !name.trim().isEmpty())
            this.name = name;
    }

    public void setVertexSource(Vertex source) {
        this.source = source;
    }

    public void setVertexDestination(Vertex destination) {
        this.destination = destination;
    }

    public String getName() {
        return name;
    }

    public Vertex getVertexSource() {
        return source;
    }

    public Vertex getVertexDestination() {
        return destination;
    }

    //ADD TO STRING?
}
