# -*- coding: utf-8 -*-
from __future__ import unicode_literals

from django.db import models, migrations


class Migration(migrations.Migration):

    dependencies = [
        ('tasks', '0003_auto_20150415_1707'),
    ]

    operations = [
        migrations.AddField(
            model_name='task',
            name='start_data',
            field=models.DateTimeField(blank=True, verbose_name='Start date', null=True),
        ),
    ]
