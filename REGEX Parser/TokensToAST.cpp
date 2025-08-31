#include "Regex.h"

void Regex::ConvertTokensToAST() {
	ASTree.Reset();
	GroupedTokens.clear();
	previousIdentifier = Identifier::None;
	insideOfConcatenationGroup = false;

	for (Token token : tokens)
	{
		ParseToken(token);
		previousIdentifier = token.GetIdentifier();
	}
	EndGroupedTokens();
}

void Regex::ParseToken(Token token) {
	Identifier id = token.GetIdentifier();
	if (id == Identifier::Alteration) {
		EndConcatenationGroup();
		return;
	}
	StartConcatenationGroup();
	GroupedTokens.push_back(token);
}

void Regex::EndGroupedTokens() {
	int groupedTokensCount = GroupedTokens.size();
	std::vector<Token> savedGroupedTokens = std::vector<Token>(GroupedTokens);
	GroupedTokens.clear();

	if (groupedTokensCount == 0) return;
	if (groupedTokensCount == 1) {
		ASTree.AddToRoot(savedGroupedTokens[0]);
		return;
	}

	ASTNode* groupParent = ASTree.AddToRoot(Token(Identifier::Alteration));
	ASTNode* currentParent = groupParent;
	for (Token token : savedGroupedTokens) {
		ParseGroupedToken(groupParent, token);
	}

	if (currentParent->GetChildCount() == 1) currentParent->MoveChildrenUp();
}

void Regex::ParseGroupedToken(ASTNode*& groupParent, Token token) {
	Identifier id = token.GetIdentifier();
	switch (id) {
		case Identifier::ConcatStart:
			groupParent = groupParent->AddChild(Token(Identifier::Concatenation));
			return;
		case Identifier::ConcatEnd:
			groupParent = groupParent->parent;
			return;
		default:
			groupParent->AddChild(token);
			return;
	}
}

void Regex::StartConcatenationGroup() {
	if (insideOfConcatenationGroup) return;
	if (previousIdentifier == Identifier::None || previousIdentifier == Identifier::Alteration) return;

	GroupedTokens.insert(GroupedTokens.end() - 1, Token(Identifier::ConcatStart));
	insideOfConcatenationGroup = true;
}

void Regex::EndConcatenationGroup() {
	if (!insideOfConcatenationGroup) return;
	insideOfConcatenationGroup = false;
	GroupedTokens.push_back(Token(Identifier::ConcatEnd));
}