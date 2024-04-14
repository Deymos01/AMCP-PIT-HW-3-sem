function MA = mirrorm(A,l)
% функция, "окружающая" матрицу A l слоями ее элементов "отраженных" от границ
    leftA = fliplr(A);
    rightA = leftA;
    upA = flipud(A);
    downA = upA;

    leftUpA = flipud(fliplr(A'));
    rightDownA = leftUpA;
    rightUpA = A';
    leftDownA = rightUpA;

    % size(x, 1) - кол-во строк
    % size(x, 2) - кол-во столбцов

    % обработка верхней и нижней отраженных
    if l < size(upA,1)
        upA = upA(size(upA,1)-l+1:size(upA,1),:);
        downA = downA(1:l,:);
    endif
    % обработка левой и правой отраженных
    if l < size(leftA,2)
        leftA = leftA(:,size(leftA,2)-l+1:size(leftA,2));
        rightA = rightA(:,1:l);
    endif
    % обработка угловых отраженных
    if l < size(leftUpA,1) % по строкам
        leftUpA = leftUpA(size(leftUpA,1)-l+1:size(leftUpA,1),:);
        rightUpA = rightUpA(size(rightUpA,1)-l+1:size(rightUpA,1),:);
        leftDownA = leftDownA(1:l,:);
        rightDownA = rightDownA(1:l,:);
    endif
    if l < size(leftUpA,2) %по столбцам
        leftUpA = leftUpA(:,size(leftUpA,2)-l+1:size(leftUpA,2));
        leftDownA = leftDownA(:,size(leftDownA,2)-l+1:size(leftDownA,2));
        rightUpA = rightUpA(:,1:l);
        rightDownA = rightDownA(:,1:l);
    endif
    MA = [leftUpA upA rightUpA; leftA A rightA; leftDownA downA rightDownA];
end
