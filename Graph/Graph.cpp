#include "Graph.h"
//Constructor
template <typename N, typename E>
gdwg::Graph<N,E>::Graph() :
    Nodes_Map{}
{};

//Destructor
template <typename N, typename E>
gdwg::Graph<N,E>::~Graph()
{
    Nodes_Map.clear();
};
//Copy constructor
template <typename N, typename E>
gdwg::Graph<N,E>::Graph(const Graph &copy){
    if(Nodes_Map != copy.Nodes_Map){
        Nodes_Map.erase(Nodes_Map.begin(),Nodes_Map.end());
        for(auto nodes: copy.Nodes_Map){
            Nodes_Map[nodes.second->Node_Value] = std::make_shared<Node>(Node{nodes.second->Node_Value});
        }
        for(auto nodes_pair:copy.Nodes_Map){
            for(auto edge: nodes_pair.second->outEdges){
                if( auto temp_s = edge->src.lock()){
                    if(auto temp_d = edge->dst.lock()){
                        this->addEdge(temp_s->Node_Value, temp_d->Node_Value, edge->Weight_Value);
                    }
                }
            }
        }
    }
}
//Move constructor
template <typename N, typename E>
gdwg::Graph<N,E>::Graph(Graph &&move) :
    Nodes_Map{std::move(move.Nodes_Map)}
    {};

//Copy assignment
template <typename N, typename E>
Graph<N,E>& gdwg::Graph<N,E>::operator=(const Graph &copy){
    //std::cout<<"a"<<std::endl;
    if(Nodes_Map != copy.Nodes_Map){
        Nodes_Map.erase(Nodes_Map.begin(),Nodes_Map.end());
        for(auto nodes: copy.Nodes_Map){
            Nodes_Map[nodes.second->Node_Value] = std::make_shared<Node>(Node{nodes.second->Node_Value});
        }
        for(auto nodes_pair:copy.Nodes_Map){
            for(auto edge: nodes_pair.second->outEdges){
                if( auto temp_s = edge->src.lock()){
                    if(auto temp_d = edge->dst.lock()){
                        this->addEdge(temp_s->Node_Value, temp_d->Node_Value, edge->Weight_Value);
                    }
                }
            }
        }
    }
    return *this;
}


//Move assignment
template <typename N, typename E>
Graph<N,E>& gdwg::Graph<N,E>::operator=(Graph &&move){
    if ((*this).Nodes_Map != move.Nodes_Map) {
        Nodes_Map = std::move(move.Nodes_Map);
				}
				return *this;
}

//isNode
template <typename N, typename E>
bool gdwg::Graph<N,E>::isNode(const N& value) const{
        if(Nodes_Map.find(value) == Nodes_Map.end()){
            return false;
        }
        else{
            return true;
            }
    }

//addNode
template <typename N, typename E>
    bool gdwg::Graph<N,E>::addNode(const N& value){
        //If node does not exist yet
        if(!isNode(value)){
            //Initialize node and store share pointer into container.
            Nodes_Map[value] = std::make_shared<Node>(Node{value});
            //Store node share pointer into fake iterator container.
            Fake_Iterator.push_back(std::make_shared<Node>(Node{value}));
            return true;
        }
        else{
            return false;
        }
    }
template <typename N, typename E>
    bool gdwg::Graph<N,E>::addEdge(const N& src, const N& dst, const E& w){
        if(!isNode(src)){
            throw std::runtime_error("src does not exist");
        }
        if(!isNode(dst)){
            throw std::runtime_error("dst does not exist");
        }
        auto src_node = Nodes_Map.find(src)->second;
        auto dst_node= Nodes_Map.find(dst)->second;
        //If one edge does not exist yet, the outEdge container of source node and inEdge container of destination should
        //not contain it as well.
        for(auto i = src_node->outEdges.begin(); i != src_node->outEdges.end();++i){
            if(auto d = (*i)->dst.lock()){
                if(d->Node_Value == dst_node->Node_Value){
                    if(w == (*i)->Weight_Value){
                        return false;
                    }
                }
            }
        }
        for(auto j = dst_node->inEdges.begin(); j != dst_node->inEdges.end();++j){
            if(auto d = (*j)->src.lock()){
                if(d->Node_Value == src_node->Node_Value){
                    if(w == (*j)->Weight_Value){
                        return false;
                    }
                }
            }
        }
        //Add egde, updating outEdges of source node and inEdges of source node.
        auto new_edge = std::make_shared<Edge>(Edge{src_node,dst_node,w});
        src_node->outEdges.insert(new_edge);
        dst_node->inEdges.insert(new_edge);
        src_node->update_degree();
        //src_node->outDegree++;
        return true;
    }

//Addedge for mergerepalce function.
template <typename N, typename E>
bool gdwg::Graph<N,E>::MergeaddEdge(const N& src, const N& dst, const E& w){

    auto src_node = Nodes_Map.find(src)->second;
    auto dst_node= Nodes_Map.find(dst)->second;
    for(auto i = src_node->outEdges.begin(); i != src_node->outEdges.end();++i){
        if(auto d = (*i)->dst.lock()){
            if(d->Node_Value == dst_node->Node_Value){
                if(w == (*i)->Weight_Value){
                    return false;
                }
            }
        }
    }
    for(auto j = dst_node->inEdges.begin(); j != dst_node->inEdges.end();++j){
        if(auto d = (*j)->src.lock()){
            if(d->Node_Value == src_node->Node_Value){
                if(w == (*j)->Weight_Value){
                    return false;
                }
            }
        }
    }
    auto new_edge = std::make_shared<Edge>(Edge{src_node,dst_node,w});
    src_node->outEdges.insert(new_edge);
    dst_node->inEdges.insert(new_edge);
    src_node->update_degree();
    //src_node->outDegree++;
    return true;
}
//printNodes
template <typename N, typename E>
void gdwg::Graph<N,E>:: printNodes() const{
    //Cause of unsortable of std::map, use temporary vector to sort nodes with the degree and value.
        std::vector<std::pair<E,N>> print_vector;
        for(auto const &pair : Nodes_Map){
            pair.second->update_degree();
            print_vector.push_back(std::make_pair(pair.second->outDegree,pair.first));
        }
        std::sort(print_vector.begin(),print_vector.end());//,sort());
        for(auto const sort_pair :print_vector){
            std::cout<<sort_pair.second<<std::endl;
        }
    }

//repalce function
template <typename N, typename E>
bool gdwg::Graph<N,E>::replace(const N& oldData, const N& newData){
        if(!isNode(oldData)){
            throw std::runtime_error("oldNode does not exist");
        }
        if(isNode(newData)){
            return false;
        }
        else{
            Nodes_Map[newData] = Nodes_Map[oldData];
            Nodes_Map[newData]-> Node_Value = oldData;
            auto old_node = Nodes_Map.find(oldData);
            Nodes_Map.erase(old_node);
            return true;
        }
    }
//printEdge
template <typename N, typename E>
void gdwg::Graph<N,E>::printEdges(const N& val) const{
        if(!isNode(val)){
            throw std::runtime_error("src does not exist");
        }
        //Again, cause of unsortable of std::map.
        std::cout<<"Edges attached to Node "<< val <<std::endl;
        std::vector<std::pair<N,E>> print_vector;
        auto src_node = Nodes_Map.find(val)->second;
        for(auto edge: src_node->outEdges){
            if((*edge).dst.lock()){
                print_vector.push_back(std::make_pair((*edge).dst.lock()->Node_Value, (*edge).Weight_Value));
            }
        }
        struct sort {
            bool operator()(const std::pair<N,E> &left, const std::pair<N,E> &right) {
                return left.second < right.second;
            }
        };
        std::sort(print_vector.begin(),print_vector.end(),sort());
        if(print_vector.size() > 0){
            for(auto edge: print_vector){
                std::cout<<edge.first<<" "<<edge.second<<std::endl;
            }
        }else{
            std::cout<<"(null)"<<std::endl;
        }
    }

//isConnect
template <typename N, typename E>
bool gdwg::Graph<N,E>::isConnected(const N& src, const N& dst) const{
        if(!isNode(src)){
            throw std::runtime_error("src does not exist");
        }
        if(!isNode(dst)){
            throw std::runtime_error("dst does not exist");
        }
        auto src_node = Nodes_Map.find(src)->second;
        auto dst_node= Nodes_Map.find(dst)->second;
        //check source node's outedges container for particular edge.
        for(auto i = src_node->outEdges.begin(); i != src_node->outEdges.end();++i){
            if(auto d = (*i)->dst.lock()){
                if(d->Node_Value == dst_node->Node_Value){
                    return true;
                }
            }
        }
        return false;
    }
//deleteNode
template <typename N, typename E>
void gdwg::Graph<N,E>::deleteNode(const N& value) noexcept {
        if(isNode(value)){
            auto src_node = Nodes_Map.find(value);
            if(src_node != Nodes_Map.end()){
                src_node->second.reset();
                Nodes_Map.erase(src_node);
            }
        }
    //update degree for all nodes.
        for(auto pairs:Nodes_Map){
            pairs.second->update_degree();
        }
    //Update fake iterator.
    auto fake_address = std::find_if(Fake_Iterator.begin(),Fake_Iterator.end(),[value](const std::shared_ptr<Node> node){
        if(node->Node_Value == value){
            return true;
        }return false;
    });
    if(fake_address != Fake_Iterator.end()){
        Fake_Iterator.erase(fake_address);
    }
                                  
    }
//delete edge
template <typename N, typename E>
void gdwg::Graph<N,E>::deleteEdge(const N& src, const N& dst, const E& w) noexcept{
        if(isNode(src) && isNode(dst)){
            //Find specific source node and destination node.
            auto src_node = Nodes_Map.find(src)->second;
            auto dst_node= Nodes_Map.find(dst)->second;
            for(auto i = src_node->outEdges.begin(); i != src_node->outEdges.end();++i){
                if(auto d = (*i)->dst.lock()){
                    //Find particular weight.
                    if(d->Node_Value == dst_node->Node_Value){
                        if(w == (*i)->Weight_Value){
                            d->inEdges.erase(*i);
                            src_node->outEdges.erase(*i);
                            src_node->update_degree();
                            break;
                        }
                    }
                }
            }
        }
    }
//mergeRepalce
template <typename N, typename E>
void gdwg::Graph<N,E>::mergeReplace(const N& oldData, const N& newData){
    if(!isNode(oldData)){
        throw std::runtime_error("Old Does not exist");
    }
    if(!isNode(newData)){
        throw std::runtime_error("New Does not exist");
    }
    auto src_node = Nodes_Map.find(oldData)->second;
    auto dst_node= Nodes_Map.find(newData)->second;
    //(nodes->oldnode) become (nodes->newnode)
    for(auto i = src_node->inEdges.begin(); i != src_node->inEdges.end();++i){
        if(auto s = (*i)->src.lock()){
            auto v = (*i)->Weight_Value;
            MergeaddEdge(s->Node_Value, newData, v);
        }
    }
    //(oldnode->nodes) become (newnode->nodes)
    for(auto j = src_node->outEdges.begin();j!= src_node->outEdges.end();++j){
        if(auto d = (*j)->dst.lock()){
            auto v_ = (*j)->Weight_Value;
            MergeaddEdge(newData, d->Node_Value, v_);
        }
    }
    deleteNode(oldData);
}

template <typename N, typename E>
void gdwg::Graph<N,E>::clear() noexcept{
    Nodes_Map.clear();
}
template <typename N, typename E>
void gdwg::Graph<N,E>::begin() const{
    Faker = 0;
}
template <typename N, typename E>
bool gdwg::Graph<N,E>::end() const{
    if(Faker >= Fake_Iterator.size()) {
       return true;
    }
    else {
        return false;
    }
}
template <typename N, typename E>
const N& gdwg::Graph<N,E>::value() const{
    return Fake_Iterator[Faker]->Node_Value;
}
template <typename N, typename E>
void gdwg::Graph<N,E>::next() const
{
    ++Faker;
}

