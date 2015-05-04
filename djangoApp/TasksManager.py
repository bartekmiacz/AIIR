#!/usr/bin/env python3

from subprocess import Popen, PIPE
from time import sleep
from datetime import datetime
import sys
import sqlite3 as sqlite

def dict_factory(cursor, row):
    d = {}
    for idx, col in enumerate(cursor.description):
        d[col[0]] = row[idx]
    return d

if __name__ == '__main__':
	con = sqlite.connect('db.sqlite3')
	con.row_factory = dict_factory

	cur = con.cursor()

	while True:
		cur.execute('SELECT * FROM tasks_task WHERE status="QE" ORDER BY create_date ASC;')
		task = cur.fetchone()

		if (task):
			cur.execute('UPDATE tasks_task SET start_date=?, status="PR" WHERE id = ?;', (datetime.now().strftime("%Y-%m-%d %H:%M:%S"), task['id']))
			con.commit()

			mpi = Popen(["mpirun", "-np", "3", "Main", str(task['number']), "5"], stdout=PIPE)
			mpi_response = mpi.communicate()[0].decode("utf-8")
			result = mpi_response.split()[0]

			if result == "TAK":
				probability = mpi_response.split()[1]
				print(result, probability)
				cur.execute('UPDATE tasks_task SET finish_date=?, result="1", status="FI", probability=? WHERE id=?;', (datetime.now().strftime("%Y-%m-%d %H:%M:%S"), probability, task['id']))
				con.commit()
			elif result == "NIE":
				print(result)
				cur.execute('UPDATE tasks_task SET finish_date=?, result="0", status="FI" WHERE id=?;', (datetime.now().strftime("%Y-%m-%d %H:%M:%S"), task['id']))
				con.commit()
			else:
				print("Backend error!")

		sleep(60)

	 
