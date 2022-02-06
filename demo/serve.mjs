#!/usr/bin/env node

import esbuildServe from "esbuild-serve";
import { promises as FS } from 'fs';

const readPackageJson = () => FS.readFile('./package.json', 'utf-8');

const getDependencies = () =>
  readPackageJson().then((packageJson) => {
    const { dependencies } = JSON.parse(packageJson);
    return Object.keys(dependencies);
  });

getDependencies()
  .then((dependencies) => {
    esbuildServe(
      {
        logLevel: "info",
        entryPoints: ["../_build/default/demo/index.bc.js"],
        bundle: true,
        outfile: "dist/bundle.js",
        sourcemap: true,
        external: dependencies,
      },
      { root: "." }
    );
  }).then(() => console.log(`Build successful`))
  .catch((error) => {
    console.error('Build fail: ' + error);
    process.exit(1);
  });

