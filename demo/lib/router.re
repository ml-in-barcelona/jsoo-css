open Js_of_ocaml;

[@deriving (sexp, compare)]
type url = {
  path: list(string),
  hash: string,
  search: string,
};

type location = {
  href: string,
  host: string,
  hostname: string,
  protocol: string,
  origin: option(string),
  port_: string,
  pathname: string,
  search: string,
  hash: string,
};

let path_of_location = location_opt =>
  switch (location_opt) {
  | None => []
  | Some(location) =>
    switch (location.pathname) {
    | ""
    | "/" => []
    | raw =>
      let raw = String.sub(raw, ~pos=1, ~len=String.length(raw) - 1);
      let raw =
        switch (raw.[String.length(raw) - 1]) {
        | '/' => String.sub(raw, ~pos=0, ~len=String.length(raw) - 1)
        | _ => raw
        };

      String.split(raw, ~on='/');
    }
  };

let hash_of_location = location_opt =>
  switch (location_opt) {
  | None => ""
  | Some(location) =>
    switch (location.hash) {
    | ""
    | "#" => ""
    | raw => String.sub(raw, ~pos=1, ~len=String.length(raw) - 1)
    }
  };

let search_of_location = location_opt =>
  switch (location_opt) {
  | None => ""
  | Some(location) =>
    switch (location.search) {
    | ""
    | "?" => ""
    | raw => String.sub(raw, ~pos=1, ~len=String.length(raw) - 1)
    }
  };

let current_url = () => {
  let js_location_opt =
    Js.some(Dom_html.window##.location) |> Js.Opt.to_option;

  let location_opt =
    Option.map(js_location_opt, ~f=js_location =>
      {
        href: js_location##.href |> Js.to_string,
        host: js_location##.host |> Js.to_string,
        hostname: js_location##.hostname |> Js.to_string,
        protocol: js_location##.protocol |> Js.to_string,
        origin:
          Js.Optdef.map(js_location##.origin, Js.to_string)
          |> Js.Optdef.to_option,
        port_: js_location##.port |> Js.to_string,
        pathname: js_location##.pathname |> Js.to_string,
        search: js_location##.search |> Js.to_string,
        hash: js_location##.hash |> Js.to_string,
      }
    );

  let path = path_of_location(location_opt);
  let hash = hash_of_location(location_opt);
  let search = search_of_location(location_opt);
  {path, hash, search};
};

/** Listen for the Dom hash change event. This binds to the event for the
    lifecycle of the application. */

let on_url_change = (~f) =>
  Js_of_ocaml.(
    Js.some(
      Dom.addEventListener(
        Dom_html.window,
        Dom_html.Event.popstate,
        Dom_html.handler((_ev: Js.t(#Dom_html.event)) => {
          f(current_url());
          Js._true;
        }),
        Js._false,
      ),
    )
  );

let route_of_url = url => Route.from_url(url.path);

let push = url => {
  let url' = Js.string(url);
  Dom_html.window##.history##pushState(
    Js.null,
    Js.string(""),
    Js.some(url'),
  );
  let event = Dom.createCustomEvent(Dom.Event.make("popstate"));
  Dom_html.window##dispatchEvent((event :> Js.t(Dom_html.event)));
};

let replace = url => {
  let url' = Js.string(url);
  Dom_html.window##.history##replaceState(Js.null, url', Js.null);
  let event = Dom.createCustomEvent(Dom.Event.make("popstate"));
  Dom_html.window##dispatchEvent((event :> Js.t(Dom_html.event)));
};

let link = (~route, content) => {
  open Incr_dom.Tyxml.Html;
  let location = Route.to_string(route);
  a(
    ~a=[
      a_onclick(event => {
        Dom.preventDefault(event);
        let _: Js.t(bool) = push(location);
        Ui_event.Ignore;
      }),
      a_href(location),
    ],
    content,
  );
};