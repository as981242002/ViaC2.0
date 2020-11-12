#include"Grammar.h"
#include"Symbol.h"

using namespace T; 

Grammar::Grammar(Compiler & compiler)
	:manager_(compiler)
{
}

void Grammar::translationUnit()
{
	while(manager_.getLex()->getToken() != TK_EOF)
	{
		externalDeclaration(StorageClass::T_GLOBAL);
	}
}

void Grammar::externalDeclaration(StorageClass level)
{

}

SymbolTypePointer Grammar::typeSpecifier()
{
	SymbolTypePointer res;
	TypeCode t = TYPE_UNDEFINED;
	int32_t token = manager_.getLex()->getToken();
	SymbolPointer ref;
	switch (token)
	{
		case KW_CHAR:
			t = TYPE_CHAR;
			break;
		case KW_SHORT:
			t = TYPE_SHORT;
			break;
		case KW_VOID:
			t = TYPE_VOID;
			break;
		case KW_INT:
			t = TYPE_INT;
			break;
		case KW_DOUBLE:
			t = TYPE_DOUBLE;
			break;
		case KW_FLOAT:
			t = TYPE_FLOAT;
			break;
		case KW_STRUCT:
			t = TYPE_STRUCT;
			ref = structSpecifier();
			break;
	}
	if (t != TYPE_UNDEFINED)
	{
		if (ref == nullptr)
			res = std::make_shared<SymbolType>(t);
		else
			res = std::make_shared<SymbolType>(t, ref);
		syntaxState_ = SyntaxState::SNTX_SP;
	}
	if (token != KW_STRUCT)
	{
		manager_.getLex()->handleToken();
	}
	return res;
}

SymbolPointer Grammar::structSpecifier()
{
	manager_.getLex()->handleToken();
	int32_t token = manager_.getLex()->getToken();
	
	syntaxState_ = SyntaxState::SNTX_DELAY;
	manager_.getLex()->handleToken();

	if(token == TK_BEGIN)
		syntaxState_ = SyntaxState::SNTX_LF_HT;
	else if(token == TK_CLOSEPA)
		syntaxState_ = SyntaxState::SNTX_NUL;
	else
		syntaxState_ = SyntaxState::SNTX_SP;
	
	syntaxIndent();

	if(token < TK_IDENT)
	{
		//hint struct id expect
	}
	SymbolPointer sym = manager_.getSymbolManager()->findStructDefine(token);
	auto type = std::make_shared<SymbolType>(KW_STRUCT);
	if(sym == nullptr){
		sym = manager_.getSymbolManager()->symPush(token | T_STRUCT, type, 0, -1);
	}
	return nullptr;
}

void Grammar::structDeclarationList(SymbolTypePointer type)
{
}

void Grammar::structDeclaration(int * maxalign, int * offset, SymbolPointer & ps)
{
}

void Grammar::declarator(SymbolTypePointer type, int * v, int * forceAlign)
{
}

void Grammar::functionCallingConvention(int * fc)
{
}

void Grammar::structMemberAlignment(int * forceAlign)
{
}

void Grammar::directDeclarator(SymbolTypePointer type, int * v, int funcCall)
{
}

void Grammar::directDeclaratorPostfix(SymbolTypePointer type, int funcCall)
{
}

void Grammar::parameterTypeList(SymbolTypePointer type, int funcCall)
{
}

void Grammar::funcbody(SymbolPointer sym)
{
}

int Grammar::isTypeSpecifier(int id)
{
	return 0;
}

void Grammar::statement(int * bsym, int * csym)
{
}

void Grammar::compoundStatement(int * bsym, int * csym)
{
}

void Grammar::ifStatement(int * bsym, int * csym)
{
}

void Grammar::forStatement(int * bsym, int * csym)
{
}

void Grammar::continueStatement(int * csym)
{
}

void Grammar::breakStatement(int * bsym)
{
}

void Grammar::returnStatement()
{
}

void Grammar::expressionStatement()
{
}

void Grammar::expression()
{
}

void Grammar::assignmentExpression()
{
}

void Grammar::equalityExpression()
{
}

void Grammar::relationalExpression()
{
}

void Grammar::additiveExpression()
{
}

void Grammar::multiplicativeExpression()
{
}

void Grammar::unaryExpression()
{
}

void Grammar::sizeofExpression()
{
}

void Grammar::postfixExpression()
{
}

void Grammar::primaryExpression()
{
}

void Grammar::argumentExpressionList()
{
}

void Grammar::printTab(int num)
{
}

void Grammar::syntaxIndent()
{
}

