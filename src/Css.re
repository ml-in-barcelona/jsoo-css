type rule =
  | Declaration(string, string)
  | Selector(string, array(rule))
  | PseudoClass(string, array(rule))
  | PseudoClassParam(string, string, array(rule));
