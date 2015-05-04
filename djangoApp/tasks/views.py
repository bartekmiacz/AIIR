from django.shortcuts import get_object_or_404, render
from django.http import HttpResponse
from django.contrib.auth.decorators import login_required
from django.contrib.auth import logout
from django.views.decorators.csrf import csrf_protect
from django.shortcuts import render_to_response
from django.http import HttpResponseRedirect
from django.template import RequestContext

from tasks.forms import *
from .models import Task

def index(request):
    return HttpResponse("AIIR")

@csrf_protect
def register(request):
    if request.method == 'POST':
        form = RegistrationForm(request.POST)
        if form.is_valid():
            user = User.objects.create_user(
            username=form.cleaned_data['username'],
            password=form.cleaned_data['password1'],
            email=form.cleaned_data['email']
            )
            return HttpResponseRedirect('/register/success/')
    else:
        form = RegistrationForm()
    variables = RequestContext(request, {
    'form': form
    })
 
    return render_to_response(
    'registration/register.html',
    variables,
    )
 
def register_success(request):
    return render_to_response(
    'registration/success.html',
    )
 
def logout_page(request):
    logout(request)
    return HttpResponseRedirect('/')
 
@login_required
def home(request):
    return render_to_response(
    'home.html',
    { 'user': request.user }
    )

@login_required
def tasks(request):
    latest_tasks_list = Task.objects.filter(user=request.user)

    context = {'latest_tasks_list': latest_tasks_list, 'user': request.user}
    return render(request, 'tasks/tasks_list.html', context)

@login_required
def add_task(request):
    if request.method == 'POST':
        form = AddTaskForm(request.POST)
        if form.is_valid():
            task = Task.objects.create_task(user=request.user, number=form.cleaned_data['number'])
        return HttpResponseRedirect('/tasks/')
    else:
        form = AddTaskForm();
    variables = RequestContext(request, {
    'form': form
    })
 
    return render_to_response(
    'tasks/add.html',
    variables,
    )

@login_required
def task_details(request, task_id):
    question = get_object_or_404(Task, pk=task_id)
    return render(request, 'tasks/detail.html', {'task': Task.objects.get(pk=task_id)})
