import Esbuild from 'esbuild';
import { promises as FS } from 'fs';

const utf8 = 'utf-8';

const readPackageJson = () => FS.readFile('./package.json', utf8);

const getDependencies = () =>
  readPackageJson().then((packageJson) => {
    const { dependencies } = JSON.parse(packageJson);
    return Object.keys(dependencies);
  });

getDependencies()
  .then((dependencies) => {
    const args = process.argv.slice(2);
    const isWatch = args.some((arg) => arg === '--watch' || arg === '-w');

    return Esbuild.build({
      watch: isWatch,
      entryPoints: ['../_build/default/demo/index.bc.js'],
      outdir: 'dist',
      platform: 'browser',
      bundle: true,
      target: ['chrome58','firefox57','safari11','edge16'],
      external: dependencies,
    });
  })
  .then(() => console.log(`Build successful`))
  .catch((error) => {
    console.error('Build fail: ' + error);
    process.exit(1);
  });
