#include "SearchSession.h"
#include "SessionCommon.h"
#include <yaml.h>


const std::string SearchSession::EXPRESSION_KEY = "expression";
const std::string SearchSession::IS_REGEX_KEY = "is-regex";
const std::string SearchSession::IS_CASE_SENSITIVE_KEY = "is-case-sensitive";

YAML::Emitter & operator<<(YAML::Emitter & out, const SearchSession & session)
{
    out << YAML::BeginMap;
    out << YAML::Key << SearchSession::EXPRESSION_KEY << YAML::Value << session.expression;
    out << YAML::Key << SearchSession::IS_REGEX_KEY << YAML::Value << session.isRegex;
    out << YAML::Key << SearchSession::IS_CASE_SENSITIVE_KEY << YAML::Value << session.isCaseSensitive;
    out << YAML::EndMap;
    return out;
}

void operator>>(const YAML::Node & in, SearchSession & session)
{
    session.expression = getValue<std::string>(in, SearchSession::EXPRESSION_KEY);
    session.isRegex = getValue<bool>(in, SearchSession::IS_REGEX_KEY); 
    session.isCaseSensitive = getValue<bool>(in, SearchSession::IS_CASE_SENSITIVE_KEY); 
}
