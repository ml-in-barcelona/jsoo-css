open Alcotest;
open Jsoo_css;

module CssForTest = {
  include Core;
  include Colors;
  include Core.Make({
    exception NotImplemented;
    let mergeStyles = _ => raise(NotImplemented);
    let make = _ => raise(NotImplemented);
    let injectRule = _ => raise(NotImplemented);
    let injectRaw = _ => raise(NotImplemented);
    let makeKeyFrames = _ => raise(NotImplemented);
  });
};

open CssForTest;

let css = v => CssForTest.make([|v|]);

let test_display_flex = () =>
  check(string, "flex", css(display(`flex)), "display: flex");

let test_color = () =>
  check(string, "hex", css(color(`hex("333"))), "color: #333");

let () =
  Alcotest.run(
    "Css",
    [
      (
        "Flex",
        [
          Alcotest.test_case(
            "should render to a valid string",
            `Quick,
            test_display_flex,
          ),
        ],
      ),
      (
        "Color",
        [
          Alcotest.test_case("should render to a Json.t", `Quick, test_color),
        ],
      ),
    ],
  );
