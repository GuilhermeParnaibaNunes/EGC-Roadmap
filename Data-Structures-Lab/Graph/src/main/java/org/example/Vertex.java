package org.example;

import java.util.HashMap;
import java.util.Map;

public class Vertex {
    private String name;
    private Map<String, Integer> degree; //Degree, in-degree e out-degree

    public Vertex(String name){
        setName(name);
        setDegree(0, 0, 0);
    }

    public void setName(String name){
        if(name != null && !name.trim().isEmpty())
            this.name = name;
    }

    public void setDegree(int degree, int inDegree, int outDegree){
        this.degree = new HashMap<>();

        this.degree.put("Degree", degree);
        this.degree.put("In-degree", inDegree);
        this.degree.put("Out-degree", outDegree);
    }

    protected void increaseInDegree(){
        degree.put("In-degree", (degree.get("In-degree")+1));
        degree.put("Degree", (degree.get("Degree")+1));
    }

    protected void increaseOutDegree(){
        degree.put("Out-degree", (degree.get("Out-degree")+1));
        degree.put("Degree", (degree.get("Degree")+1));
    }

    protected void resetDegree(){
        setDegree(0, 0, 0);
    }

    public String getName() {
        return name;
    }

    public Map<String, Integer> getDegree() {
        return degree;
    }
}
