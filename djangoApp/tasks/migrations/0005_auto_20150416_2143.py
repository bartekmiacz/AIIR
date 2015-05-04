# -*- coding: utf-8 -*-
from __future__ import unicode_literals

from django.db import models, migrations


class Migration(migrations.Migration):

    dependencies = [
        ('tasks', '0004_task_start_data'),
    ]

    operations = [
        migrations.AddField(
            model_name='task',
            name='probability',
            field=models.FloatField(blank=True, null=True),
        ),
        migrations.AddField(
            model_name='task',
            name='result',
            field=models.BooleanField(default=False),
        ),
        migrations.AlterField(
            model_name='task',
            name='status',
            field=models.CharField(default='QE', max_length=2, choices=[('QE', 'In queue'), ('PR', 'In progress'), ('FI', 'Finished'), ('AB', 'Aborted')]),
        ),
    ]
