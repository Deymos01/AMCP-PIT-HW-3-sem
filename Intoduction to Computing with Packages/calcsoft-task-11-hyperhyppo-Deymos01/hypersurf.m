function hypersurf(A)
    if ishyper(A)
        V = eig(A(1:3,1:3));
        [X, Y] = meshgrid(linspace(-5,5,100), linspace(-5,5,100));
        I2 = det(A(1:2,1:2)) + det(A(2:3,2:3)) + det([A(1,1) A(1,3); A(1,3) A(3,3)]);
        I3 = det(A(1:3,1:3));
        I4 = det(A);

        if I3 == 0 % гиперболический параболоид
            if abs(V(1)) < 1e-8
                V(1) = V(3);
            elseif abs(V(2)) < 1e-8
                V(2) = V(3);
            endif
            k1 = -1/2*V(1)*sqrt(-I2/I4);
            k2 = -1/2*V(2)*sqrt(-I2/I4);
            Z = k1 .* (X.^2) + k2 .* (Y.^2);
        else % Однополостный гиперболоид
            Z = real(sqrt((-I4/I3-V(1)*(X.^2)-V(2)*(Y.^2))*1/V(3)));
            Z1 = -1 .* Z;
            surf(X, Y, Z1);
        endif

        surf(X, Y, Z);
        axis equal;
        xlabel('X'); ylabel('Y'); zlabel('Z');
        colormap ocean;
        shading interp;
    endif
end
