//
// Created by Nicolas on 06/10/2022.
//

#include "merkle.h"

namespace merkle {
    bool merkle::MerkleNode::IsValid() const {
        if (IsLeaf()) {
            return hash() == sha256(value_);
        } else {
            return left_->IsValid() && right_->IsValid();
        }
    }

    std::string merkle::MerkleNode::hash() const { return hash_; }

    std::string merkle::MerkleNode::value() const { return value_; }

    bool merkle::MerkleNode::IsLeaf() const {
        return (left_ == nullptr) && (right_ == nullptr);
    }

    bool operator==(const merkle::MerkleNode &lhs,
                    const merkle::MerkleNode &rhs) {
        // First the trivial case of identity.
        if (&lhs == &rhs) {
            return true;
        }

        // Both nodes must be either leaf, or non-leaf.
        if (lhs.IsLeaf() != rhs.IsLeaf()) {
            return false;
        }

        // Finally, the hash values themselves.
        return lhs.hash() == rhs.hash();
    }

    inline bool operator!=(const merkle::MerkleNode &lhs,
                           const merkle::MerkleNode &rhs) {
        return !(lhs == rhs);
    }

    merkle::MerkleNode * Build(DoubleList<std::string> &values) {
        DoubleList<merkle::MerkleNode*> nodes;
        for (const auto & value: values){
            nodes.push_back(new merkle::MerkleNode(value));
        }

        while (nodes.size() > 1) {

            int n=0;
            if (nodes.size() % 2 != 0) nodes.push_back(nodes.back());

            DoubleList<merkle::MerkleNode*> new_nodes;
            merkle::MerkleNode* aux;
            for ( const auto & nodo: nodes){
                if (n%2 != 0) {
                    auto temp = new merkle::MerkleNode(aux, nodo);
                    new_nodes.push_back(temp);
                }
                aux = nodo;
                n++;
            }
            nodes = new_nodes;
        }
        return nodes.front();
    }
}