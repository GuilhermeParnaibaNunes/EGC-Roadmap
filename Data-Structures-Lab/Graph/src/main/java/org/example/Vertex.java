package org.example;

public class Vertex {
    private String name;

    public Vertex(String name){
        setName(name);
    }

    public void setName(String name){
        if(name != null && !name.trim().isEmpty())
            this.name = name;
    }

    public String getName() {
        return name;
    }
}
