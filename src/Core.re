module type API = {
  type t;
  let toJson: array(Css.rule) => t;
  let mergeStyles: (. array(string)) => string;
  let injectRules: (. string, t) => unit;
  let injectRaw: (. string) => unit;
  let make: (. t) => string;
  let global: (. string, array(Css.rule)) => unit;
  let keyframe: (. array((int, array(Css.rule)))) => string;
};

module Make = (Implementation: API) => {
  type t = Implementation.t;
  let merge = Implementation.mergeStyles;
  let insertRule = Implementation.injectRaw;
  let make = s => Implementation.make(Implementation.toJson(s));
  let global = Implementation.global
  let keyframe = Implementation.keyframe;
};
