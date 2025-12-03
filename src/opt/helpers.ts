import fs from "node:fs/promises";
import path from "node:path";
import ts from "typescript";

const resolvePath = ts.sys.resolvePath;
const fileExists = ts.sys.fileExists;
const deleteFile = ts.sys.deleteFile;
const directoryExists = ts.sys.directoryExists;
const createDirectory = ts.sys.createDirectory;
const writeFile = ts.sys.writeFile;

const wait = (time: number) =>
	new Promise((resolve) => setTimeout(resolve, time));
const writeOutFile = (filePath: string, content: string) => {
	const resolvedPath = resolvePath(filePath);
	const dir = path.dirname(resolvedPath);
	if (fileExists(resolvedPath) && typeof deleteFile === "function") {
		deleteFile(resolvedPath);
	} else {
		if (!directoryExists(dir)) {
			createDirectory(dir);
		} else {
			if (typeof deleteFile === "function") {
				deleteFile(resolvedPath);
			}
		}
	}
	writeFile(resolvedPath, content);
};

async function clear(folderPath: string) {
	folderPath = path.resolve(process.cwd(), folderPath);
	try {
		const entries = await fs.readdir(folderPath, {
			withFileTypes: true,
		});
		await Promise.all(
			entries.map((entry) =>
				fs.rm(path.join(folderPath, entry.name), { recursive: true }),
			),
		);
	} catch (error: unknown) {
		const code = (error as { code?: string } | undefined)?.code;
		if (code !== "ENOENT") {
			throw error;
		}
	}
}

export { wait, writeOutFile, clear };
