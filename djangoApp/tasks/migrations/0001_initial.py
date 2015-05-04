# -*- coding: utf-8 -*-
from __future__ import unicode_literals

from django.db import models, migrations
from django.conf import settings


class Migration(migrations.Migration):

    dependencies = [
        migrations.swappable_dependency(settings.AUTH_USER_MODEL),
    ]

    operations = [
        migrations.CreateModel(
            name='Task',
            fields=[
                ('id', models.IntegerField(serialize=False, primary_key=True)),
                ('number', models.IntegerField()),
                ('create_date', models.DateTimeField(verbose_name='Create date')),
                ('finish_date', models.DateTimeField(verbose_name='Finish date')),
                ('status', models.CharField(choices=[('QE', 'In queue'), ('PR', 'In progress'), ('FI', 'Finished')], max_length=2, default='QE')),
                ('user', models.ForeignKey(to=settings.AUTH_USER_MODEL)),
            ],
        ),
    ]
