#include <Parsers/ParserModelDeclaration.h>
#include <Parsers/CommonParsers.h>
#include <Parsers/ExpressionElementParsers.h>
#include <Parsers/ASTLiteral.h>
#include <Parsers/ASTIdentifier_fwd.h>
#include <Parsers/ASTModelDeclaration.h>


namespace DB
{

bool ParserModelDeclaration::parseImpl(Pos & pos, ASTPtr & node, Expected & expected)
{
    ParserKeyword s_target_column(Keyword::TARGET_COLUMN);
    ParserKeyword s_algorithm(Keyword::ALGORITHM);
    ParserCompoundIdentifier parser_name;
    ParserStringLiteral parser_target_column;
    ParserStringLiteral parser_algorithm;

    auto model_declaration = std::make_shared<ASTModelDeclaration>();

    ASTPtr name;
    if (!parser_name.parse(pos, name, expected))
        return false;

    tryGetIdentifierNameInto(name, model_declaration->name);

    if (!s_target_column.ignore(pos, expected))
        return false;

    ASTPtr target_column;
    if (!parser_target_column.parse(pos, target_column, expected))
        return false;

    model_declaration->target_column = target_column;

    if (!s_algorithm.ignore(pos, expected))
        return false;

    ASTPtr algorithm;
    if (!parser_algorithm.parse(pos, algorithm, expected))
        return false;

    model_declaration->algorithm = algorithm;

    node = model_declaration;
    return true;
}

}
