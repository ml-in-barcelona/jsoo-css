(lang dune 2.0)
(name jsoo-css)

(source
 (github ml-in-barcelona/jsoo-css))

(license MIT)
(authors "davesnx")
(maintainers "davesnx")

(generate_opam_files true)

(package
 (name jsoo-css)
 (synopsis "CSS Typed functional interface in jsoo")
 (description "CSS Typed functional interface in jsoo, bindings to inline styles and emotion")
 (depends
  (ocaml (>= 4.10.2))
  (dune (>= 2.0))
  (reason (>= 3.7.0))
  (gen_js_api (and (>= 1.0.7) (< 1.1.0)))
  js_of_ocaml
  js_of_ocaml-ppx
  (odoc :with-doc)
  (ocamlformat :dev)
  (dune-release :dev)
  (ocaml-lsp-server :dev)
  (jsoo-react :dev)
  (pastel :dev)
  (cli :dev)
  (file-context-printer :dev)
  (rely :dev)
 )
)
