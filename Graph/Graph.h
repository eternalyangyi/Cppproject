//
//  Graph.h
//  Graph
//
//  Created by yy on 17/9/17.
//  Copyright © 2017 yy. All rights reserved.
//

#ifndef Graph_h
#define Graph_h
#include <algorithm>
#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <utility>
#include <memory>
#include <typeinfo>
namespace gdwg{
    template <typename N, typename E>
    class Graph{
        class Node;
        class Edge;
        
        
        public:
        
        Graph();
        
        ~Graph();
        
        Graph(const Graph& copy);
        
        Graph(Graph&& move);
        
        Graph& operator=(const Graph& copy);
        
        Graph& operator=(Graph&& move);
        
        bool isNode(const N& value) const;
        
        bool addNode(const N& value);
        
        bool addEdge(const N& src, const N& dst, const E& w);
        
        bool MergeaddEdge(const N& src, const N& dst, const E& w);
        
        void printNodes() const;
        
        bool replace(const N& oldData, const N& newData);
        
        void printEdges(const N& val)const;
        
        bool isConnected(const N& src, const N& dst) const;
        
        void deleteNode(const N& value) noexcept;
        
        void deleteEdge(const N& src, const N& dst, const E& w) noexcept;
        
        void mergeReplace(const N& oldData, const N& newData);
        
        void clear() noexcept;
        
        void begin() const;
        
        bool end() const;
        
        void next() const;
        
        const N& value() const;
        
        private:
        //Node class
        //Storing both incoming edges and outgoing edges for convenience of mergereplace function.
        class Node{
            public:
                N Node_Value;
                std::set<std::shared_ptr<Edge> > outEdges;
                std::set<std::shared_ptr<Edge> > inEdges;
                int outDegree;
                Node(){};
        
                Node(const N& value) : Node_Value{value}{
                    outDegree = 0;
                }
                ~Node(){
                    outEdges.clear();
                    inEdges.clear();
                }
            //Function designed for update nodes' outdegree after deleting nodes or edges.
            void update_degree(){
                for( auto i = outEdges.begin(); i != outEdges.end();){
                    if((*i)->dst.lock()){
                        ++i;
                    }else{
                        outEdges.erase(i++);
                    }
                }
                outDegree = outEdges.size();
                for( auto i = inEdges.begin(); i != inEdges.end();){
                    if((*i)->src.lock()){
                        ++i;
                    }else{
                        inEdges.erase(i++);
                    }
                }
            }
        
            };
        class Edge{
            public:
                //Storing source nodes and destination nodes as weak pointers.
                E Weight_Value;
                std::weak_ptr<Node> src;
                std::weak_ptr<Node> dst;
            
                Edge(){};
                Edge(std::shared_ptr<Node> origin_node, std::shared_ptr<Node> destination_node, E weight)
            :Weight_Value{weight} {
                    src = origin_node;
                    dst = destination_node;
        }
            ~Edge(){
                src.reset();
                dst.reset();
            }
        };
        
        std::map<N,std::shared_ptr<Node>> Nodes_Map;
        std::vector<std::shared_ptr<Node>> Fake_Iterator;
        mutable unsigned int Faker;

        
    };
    #include "Graph.tem"
}

#endif /* Graph_h */
