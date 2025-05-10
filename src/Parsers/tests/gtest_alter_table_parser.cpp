#include <Parsers/ASTModelDeclaration.h>
#include <Parsers/ASTLiteral.h>
#include <Parsers/ParserAlterQuery.h>
#include <Parsers/parseQuery.h>

#include <gtest/gtest.h>

using namespace DB;

TEST(ParserAlterTableAddModel, Basic)
{
    String input =
        "ALTER TABLE new.table ADD MODEL clf"
        "  TARGET COLUMN 'column'"
        "  ALGORITHM 'algo'";

    ParserAlterQuery parser;
    ASTPtr ast = parseQuery(parser, input.data(), input.data() + input.size(), "", 0, 0, 0);

    EXPECT_TRUE(ast);
    ASTAlterQuery * alter = ast->as<ASTAlterQuery>();
    EXPECT_TRUE(alter);

    auto * cmd = alter->command_list->children[0]->as<ASTAlterCommand>();
    EXPECT_EQ(cmd->type, ASTAlterCommand::ADD_MODEL);

    auto * model_decl = cmd->model_decl->as<ASTModelDeclaration>();
    EXPECT_TRUE(model_decl);
    EXPECT_EQ(model_decl->name, "clf");

    EXPECT_TRUE(model_decl->target_column);
    auto * target_column = model_decl->target_column->as<ASTLiteral>();
    EXPECT_TRUE(target_column);
    EXPECT_EQ(target_column->value, "column");

    EXPECT_TRUE(model_decl->algorithm);
    auto * algorithm = model_decl->algorithm->as<ASTLiteral>();
    EXPECT_TRUE(algorithm);
    EXPECT_EQ(algorithm->value, "algo");
}
