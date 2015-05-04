from django.db import models
from django.contrib.auth.models import User
from datetime import datetime

# Create your models here.

class TaskManager(models.Manager):
	def create_task(self, number, user):
		task = self.create(number=number, user=user, create_date=datetime.now(), status='QE')
		return task;

class Task(models.Model):
	id = models.AutoField(primary_key=True)
	user = models.ForeignKey(User)
	number = models.IntegerField()
	result = models.BooleanField(blank=True, default=False)
	probability = models.FloatField(blank=True, null=True)
	create_date = models.DateTimeField('Create date')
	start_date = models.DateTimeField('Start date', blank=True, null=True)
	finish_date = models.DateTimeField('Finish date', blank=True, null=True)

	IN_QUEUE = 'QE'
	IN_PROGRESS = 'PR'
	FINISHED = 'FI'
	ABORTED = 'AB'

	STATUS_CHOICE = (
		(IN_QUEUE, 'In queue'),
		(IN_PROGRESS, 'In progress'),
		(FINISHED, 'Finished'),
		(ABORTED, 'Aborted')
	)

	status = models.CharField(max_length=2, choices=STATUS_CHOICE, default=IN_QUEUE)

	objects = TaskManager()

