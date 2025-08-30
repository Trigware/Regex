#include "Regex.h"

ASTNode* ASTNode::AddChild(const Token& t) {
	std::unique_ptr<ASTNode> child = GetNodePtr(t);
	child->parent = this;
	children.push_back(std::move(child));
	return children.back().get();
}

void AST::Reset() {
	root.reset();
	Token rootToken(Identifier::ASTRoot);
	root = ASTNode::GetNodePtr(rootToken);
}

std::unique_ptr<ASTNode> ASTNode::GetNodePtr(Token t) {
	return std::make_unique<ASTNode>(t);
}

ASTNode* AST::AddToRoot(const Token& t) {
	return root->AddChild(t);
}

void AST::PrintTree() {
	root.get()->PrintNode(NodePosition::Root);
}

void ASTNode::PrintNode(NodePosition positionInChildList, std::wstring prefix) {
	std::wstring branch = L"";
	switch (positionInChildList) {
		case NodePosition::Other: branch = L"├─  "; break;
		case NodePosition::LastChild: branch = L"└─  "; break;
	}

	std::wstring nodeOutput = prefix + branch + token.GetTokenAsString();
	std::wcout << nodeOutput << std::endl;

	std::wstring childPrefix = prefix;
	switch (positionInChildList) {
		case NodePosition::Other: childPrefix += L"│   "; break;
		case NodePosition::LastChild: childPrefix += L"    "; break;
	}

	int childrenCount = children.size();
	for (int i = 0; i < childrenCount; i++) {
		NodePosition nodePos = NodePosition::Other;
		if (i + 1 == childrenCount) nodePos = NodePosition::LastChild;
		children[i]->PrintNode(nodePos, childPrefix);
	}
}

void Regex::ConvertTokensToAST() {
	ASTree.Reset();
	for (Token token : tokens) {
		ASTree.AddToRoot(token);
	}
}