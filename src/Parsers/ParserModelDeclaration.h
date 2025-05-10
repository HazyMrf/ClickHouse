#pragma once

#include <Parsers/IParserBase.h>

namespace DB
{

/// Parser for 'ALTER TABLE t ADD MODEL m TARGER COLUMN c ALGORITH a SETTINGS ...'
/// Produce ASTModelDeclaration.
class ParserModelDeclaration : public IParserBase
{
protected:
    const char * getName() const override { return "ModelDeclaration"; }
    bool parseImpl(Pos & pos, ASTPtr & node, Expected & expected) override;
};

}
