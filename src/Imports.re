type emotion = Ojs.t;
let emotion_to_js = v => v;
let emotion: emotion = Js_of_ocaml.Js.Unsafe.js_expr({|require("@emotion/css")|});
