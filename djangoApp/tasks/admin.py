from django.contrib import admin
from .models import Task

class TaskAdmin(admin.ModelAdmin):
	list_display = ('number', 'user', 'status')

admin.site.register(Task, TaskAdmin)
