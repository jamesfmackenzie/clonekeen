
// this can't be in token.h because ml_header and token have a sort
// of circular dependency going on.

token *tokenize(char *line);
token *tokenize_const(const char *line);
char assemble_token(token *firsttoken, char *str, ml_header *header, int src);
void token_cleanup(token *firsttoken);
