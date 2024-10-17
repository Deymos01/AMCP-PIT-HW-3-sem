function hyperplot(A)
    if ishyper(A)
        t = linspace(-pi, pi, 200);
        lines = zeros(3, length(t));
        for it = 1:length(t)
            x = cos(t(it));
            y = sin(t(it));
            z = t(it);
            lines(:,it) = [x;y;z];
        endfor

        plot3(lines(1,:),lines(2,:),lines(3,:),'linewidth', 1.5);
        xlabel('X'); ylabel('Y'); zlabel('Z');
        axis equal;
        hold on;

        hypersurf(A);
    endif
endfunction
