(The file `/home/ptm/Documents/NPMS/julian-day/readme.md` exists, but is empty)

## Scripts

`src/printCycles.mts` — small CLI script that prints cycle positions (Solar, Metonic, Indiction, Julian Period) for a range of years.

Usage (with Node+TS setup):

```bash
# type-check
npx tsc --noEmit

# run the script with Node + native ESM + loader that understands .mts, or run via a bundler/ts-node. Example (single year):
# node --loader ts-node/esm ./src/printCycles.mts 2000 2025

# or run via ts-node if installed:
npx ts-node-esm src/printCycles.mts 2000 2025
```

If you want, I can add a small NPM script to run this directly.
