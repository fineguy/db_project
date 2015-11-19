# db_project
This is a simple database browser and editor for my course in databases.
Use username: user and password: pass to access it.

## Description
There are different departments, chairs and professors at our university. The user should be able to view the list of professors possibly limited to a chair or a department. The user should also be able to modify all info.

## Database structure
There are five tables in the faculty database:

1. Users table – used to store usernames and logins. Immutable.
2. Departments table – holds info about Deans' names, keys and department names.
3. Chairs table – holds info about names of chairs and keys of their respectful departments.
4. Roster table – connects professors and chairs.
5. Professors table – store professors' names and years of service.

## Use cases
There are two screens seen for the user after successful login. The first one is used only for browsing professors, and the second one allows the user to perform three actions on three tables (Departments, Chairs and Professors):
* Add – by specifying a table and all related data, the user creates a new entry to the table.
* Edit – modifies an existing entry in the specified table.
* Remove – deletes an entry.
