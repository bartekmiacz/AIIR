from django.conf.urls import include, url, patterns
from django.contrib import admin
from tasks.views import *

urlpatterns = [
    url(r'^$', 'django.contrib.auth.views.login'),
    url(r'^logout/$', logout_page),
    url(r'^accounts/login/$', 'django.contrib.auth.views.login'), # If user is not login it will redirect to login page
    url(r'^register/$', register),
    url(r'^register/success/$', register_success),
    url(r'^home/$', home),
    url(r'^tasks/$', tasks),
    url(r'^tasks/add/$', add_task),
    url(r'^tasks/(?P<task_id>[0-9]+)/$', task_details),
    url(r'^admin/', include(admin.site.urls)),
]
