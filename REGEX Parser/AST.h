#pragma once
#include <vector>
#include <memory>
#include "Token.h"

enum class NodePosition {
	Root,
	LastChild,
	Other
};

class ASTNode {
public:
	Token token;
	ASTNode(Token t) : token(t) {}
	std::vector<std::unique_ptr<ASTNode>> children;
	ASTNode* parent = nullptr;
	static std::unique_ptr<ASTNode> GetNodePtr(Token t);
	ASTNode* AddChild(const Token& t);
	ASTNode* AddSibling(const Token& t) { return parent->AddChild(t); }
	void PrintNode(NodePosition parentNodePosition, std::wstring prefix = L"");
};

class AST {
public:
	std::unique_ptr<ASTNode> root;
	AST() { Reset(); }
	void Reset();
	ASTNode* AddToRoot(const Token& t);
	void PrintTree();
	StringType GetRootTokenAsStr() { return root.get()->token.IdentifierAsString(); }
};