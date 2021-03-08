type t =
  | Home;

let from_url =
  fun
  | [] => Some(Home)
  | _ => None;

let to_string =
  fun
  | Home => "/";
