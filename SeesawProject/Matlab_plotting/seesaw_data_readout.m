%% Seesaw project: Data readout
% Julian Zilly

% INSTRUCTIONS:
% This script plots your results for the Seesaw, including your reference
% signal, measurement signal and output signal. 

% All you need to change is where to save the pdf files of the figures to.
% This is labeled with "CHANGE HERE"

% Clear all data, close all figures (tabula rasa)
clc; clear all; close all;
% Adding the home directory/seesawState folder to known directories

% CHANGE HERE: Provide the correct path to your home folder - 
% might be the same as the provided path
addpath('~/seesawState')  
% --------------------------------------------------------------------
% CHANGE HERE: Provide the correct path to your report folder - similar to
% the existing one
% --------------------------------------------------------------------
% --------------------------------------------------------------------
path = '../Seesaw_project_report_template/figures/';
% --------------------------------------------------------------------
% --------------------------------------------------------------------


% DESCRIPTION OF DATA:
% Column 1 is time t
% Column 2 is reference signal r
% Column 3 is measurement signal y
% Column 4 is input signal u

%% TASK 1 - seesawState_task1

% Read in data:
Data = seesawState_task1;
t = Data(:, 1);
dt = Data(30, 1)-Data(29, 1);
r = Data(:,2);
y = Data(:,3);
u = Data(:, 4);

% --------------------------------------------------------------------

task_string = 'task1';
save_figures(path, t, r, y, u, task_string);

% --------------------------------------------------------------------


% --------------------------------------------------------------------
% Error metrics: How do you measure how well the controller is working?
% --------------------------------------------------------------------

% Task 1 - Measures the average absolute error of the measurements 
%          from the trajectory

Error_task1 = norm(r - y)/length(r)


%% TASK 2 - seesawState_task2

% Read in data:
Data = seesawState_task2;
t = Data(:, 1);
dt = Data(30, 1)-Data(29, 1);
r = Data(:,2);
y = Data(:,3);
u = Data(:, 4);

% --------------------------------------------------------------------

task_string = 'task2';
save_figures(path, t, r, y, u, task_string);

% --------------------------------------------------------------------


% ------------------------
% Calculating rise time t_90 and overshoot M_p
% ------------------------
jump_size = 5000;

% ------------------------
% OVERSHOOT
% ------------------------
[M_p, t_90] = step_response_analysis(r, y, jump_size, dt)

% ------------------------
% UNDERSHOOT
% ------------------------
[M_p_neg, t_90_neg] = step_response_analysis(-r, -y, jump_size, dt)

% --------------------------------------------------------------------
% Error metrics: How do you measure how well the controller is working?
% --------------------------------------------------------------------

% Task 2 - Specify starting point - Then overshoot and rise time will be
% calculated

Error_task2 = norm(r - y)/length(r)


%% TASK 3 without ARW - seesawState_task3_no_ARW

% Read in data:
Data = seesawState_task3_no_ARW;
t = Data(:, 1);
dt = Data(30, 1)-Data(29, 1);
r = Data(:,2);
y = Data(:,3);
u = Data(:, 4);


% --------------------------------------------------------------------
task_string = 'task3_no_ARW';
save_figures(path, t, r, y, u, task_string);
% --------------------------------------------------------------------


% --------------------------------------------------------------------
% Error metrics: How do you measure how well the controller is working?
% --------------------------------------------------------------------

% Task 3 - How does the overshoot increase/decrease with and without
% anti-reset windup (ARW)?

% ------------------------
% OVERSHOOT
% ------------------------
jump_size = 5000;
[M_p, t_90] = step_response_analysis(r, y, jump_size, dt)


%% TASK 3 WITH ARW - seesawState_task3_ARW

% Read in data:
Data = seesawState_task3_ARW;
t = Data(:, 1);
dt = Data(30, 1)-Data(29, 1);
r = Data(:,2);
y = Data(:,3);
u = Data(:, 4);

% --------------------------------------------------------------------
task_string = 'task3_ARW';
save_figures(path, t, r, y, u, task_string);
% --------------------------------------------------------------------

% --------------------------------------------------------------------
% Error metrics: How do you measure how well the controller is working?
% --------------------------------------------------------------------

% Task 3 - How does the overshoot increase/decrease with and without
% anti-reset windup (ARW)?

% ------------------------
% OVERSHOOT
% ------------------------
jump_size = 5000;
[M_p, t_90] = step_response_analysis(r, y, jump_size, dt)
