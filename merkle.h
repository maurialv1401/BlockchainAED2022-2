#ifndef PRAED_MERKLE_H
#define PRAED_MERKLE_H


#include "sha256.h"
#include <memory>
#include <iostream>
#include <cassert>
#include <memory>

#include <utility>
#include <algorithm>
#include <string>
#include "double.h"

namespace merkle{

class MerkleNode {
 protected:
  MerkleNode * left_;
  MerkleNode * right_;
  std::string hash_;
  std::string value_;

 public:
    MerkleNode():left_(nullptr), right_(nullptr), value_("-1"){}

    explicit MerkleNode(const std::string &value) : value_(value), left_(nullptr), right_(nullptr) {
        hash_ = sha256(value);
    }

  MerkleNode(MerkleNode *left,
             MerkleNode *right) {
    left_ = left;
    right_ = right;
    hash_ = sha256(left->hash_+right->hash_);
  }

  virtual ~MerkleNode() = default;

  bool IsValid() const;

  std::string hash() const;

  std::string value() const;

  bool IsLeaf() const;

  const MerkleNode *left() const { return left_; }
  const MerkleNode *right() const { return right_; }
};

bool operator==(const merkle::MerkleNode &lhs,
                const merkle::MerkleNode &rhs);

inline bool operator!=(const merkle::MerkleNode &lhs,
                           const merkle::MerkleNode &rhs);

merkle::MerkleNode * Build(DoubleList<std::string> &values);

inline std::ostream& operator<<(std::ostream& out,
        merkle::MerkleNode* root) noexcept;

}
#endif //PRAED_MERKLE_H