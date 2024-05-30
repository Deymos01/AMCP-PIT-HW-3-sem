function [t,x] = pendux2(link1,link2, theta,ts)
% Здесь можем использовать link1.m и link1.l, link2.m и link2.l, theta0(1) и theta0(2), ts(1) и ts(2)
% x - массив (4 х n),
% x(1,:) - x- координаты конца первого звена,
% x(2,:) - y- координаты конца первого звена,
% x(3,:) - x- координаты конца второго звена,
% x(4,:) - y- координаты конца второго звена
    l1 = link1.l; m1 = link1.m; l2 = link2.l; m2 = link2.m;
    th1 = theta(1); th2 = theta(2);
    ts1 = ts(1); ts2 = ts(2);

    [t, y] = ode45(@(t, y) computeDoublePendulumODE(t, y, [link1, link2]), ts, [th1, 0, th2, 0], odeset('RelTol', 1e-6, 'AbsTol', 1e-6));
    th1 = y(:,1); th2 = y(:,3);

    x = [l1*sin(th1), -l1*cos(th1), l1*sin(th1) + l2*sin(th2), -l1*cos(th1) - l2*cos(th2)]';
endfunction

function dydt = computeDoublePendulumODE(~, y, p)
    g = 9.81;
    % Extract parameters
    L1 = p(1).l;  % Length of first pendulum
    m1 = p(1).m;  % Mass of first pendulum

    L2 = p(2).l;  % Length of second pendulum
    m2 = p(2).m;  % Mass of second pendulum

    % Extract state variables
    th1 = y(1); om1 = y(2); th2 = y(3); om2 = y(4);

    % Calculate the difference in angles
    sinDTh = sin(th2 - th1);
    cosDTh = cos(th2 - th1);

    sinTh1 = sin(th1);
    sinTh2 = sin(th2);

    % Equations of motion
    numer1 = m2 * g * sinTh2 * cosDTh - m2 * sinDTh * (L1 * om1^2 * cosDTh + L2 * om2^2) - (m1 + m2) * g * sinTh1;
    denom1 = L1 * (m1 + m2 * sinDTh^2);
    numer2 = (m1 + m2) * (L1 * om1^2 * sinDTh - g * sinTh2 + g * sinTh1 * cosDTh) + m2 * L2 * om2^2 * sinDTh * cosDTh;
    denom2 = L2 * (m1 + m2 * sinDTh^2);

    % Initialize the derivative vector
    dydt = [om1; numer1 / denom1; om2; numer2 / denom2];
endfunction
