// SPDX-License-Identifier: GPL-2.0-or-later
/*
 * src/file.c
 *
 * File handling functions
 *
 * Copyright (C) 2018-2020 SCANOSS.COM
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

 /**
  * @file file.c
  * @date 12 Jul 2020 
  * @brief LDB file management functions
 
  * //TODO Long description
  * @see https://github.com/scanoss/ldb/blob/master/src/file.c
  */

/**
 * @brief create LDB directory
 * 
 * @param path string path
 */
void ldb_prepare_dir(char *path)
{
	if (ldb_dir_exists (path)) return;
	if (mkdir (path, 0755)) 
		ldb_error ("E050 Cannot create root LDB directory");
}

/**
 * @brief Check if exist a LDB file
 * 
 * @param path string path
 * @return true if the file exist
 */
bool ldb_file_exists(char *path)
{
	struct stat pstat;
	if (!stat(path, &pstat))
		if (S_ISREG(pstat.st_mode))
			return true;
	return false;
}

/**
 * @brief Check if the LDB directory exist
 * 
 * @param path path string
 * @return true if exist
 */
bool ldb_dir_exists(char *path)
{
	struct stat pstat;
	if (!stat(path, &pstat))
		if (S_ISDIR(pstat.st_mode))
			return true;
	return false;
}

/**
 * @brief Return the file size for path
 * 
 * @param path string path
 * @return file size
 */
uint64_t ldb_file_size(char *path)
{
	FILE *fp = fopen(path, "r");
	if (!fp) return 0;

	fseeko64(fp, 0, SEEK_END);
	uint64_t size = ftello64(fp);
	fclose(fp);

	return size;
}

/**
 * @brief Check if LDB root directory exist
 * 
 * @return true if exist
 */
bool ldb_check_root()
{
	if (!ldb_dir_exists(ldb_root))
	{
		printf("E059 LDB root directory %s is not accessible\n", ldb_root);
		return false;
	}
	return true;
}

/**
 * @brief Checks if a db/table already exists
 * 
 * @param db DB name string
 * @param table name string
 * @return true if exist
 */
bool ldb_table_exists(char *db, char*table)
{
	char *path = malloc(LDB_MAX_PATH);
	sprintf(path, "%s/%s/%s", ldb_root, db, table);
	bool out = ldb_dir_exists(path);
	free(path);
	return out;
}

/**
 * @brief Checks if a db already exists
 * 
 * @param db db string path
 * @return true if exist
 */
bool ldb_database_exists(char *db)
{
	char *path = malloc(LDB_MAX_PATH);
	sprintf(path, "%s/%s", ldb_root, db);
	bool out = ldb_dir_exists(path);
	free(path);
	return out;
}
