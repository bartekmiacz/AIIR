# -*- coding: utf-8 -*-
from __future__ import unicode_literals

from django.db import models, migrations


class Migration(migrations.Migration):

    dependencies = [
        ('tasks', '0005_auto_20150416_2143'),
    ]

    operations = [
        migrations.RenameField(
            model_name='task',
            old_name='start_data',
            new_name='start_date',
        ),
    ]
