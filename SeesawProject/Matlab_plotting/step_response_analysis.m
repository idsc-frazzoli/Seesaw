function [M_p, t_90] = step_response_analysis(r, y, jump_size, dt)
% ------------------------
% OVERSHOOT
% ------------------------
% Find subparts of vector where the max should be calculated

r_max_mask = r > jump_size/2;
find_where = r_max_mask(2:end) - r_max_mask(1:end-1);
starts = find_where == 1;
ends = find_where == -1;

range = 1:length(r);
range_starts = range(starts);
range_ends = range(ends);

if range_starts(1) > range_ends(1)
    range_starts = range_starts(1:end-1);
    range_ends = range_ends(2:end);
end

if length(range_starts) > length(range_ends)
    range_starts = range_starts(1:length(range_ends));
end

maximal_overshoot = 0;
t_90_slowest = 0;
for s=1:length(range_starts)
    maximal_overshoot = max(maximal_overshoot, max(y(range_starts(s):range_ends(s))-jump_size));
    t_90_where = y(range_starts(s):range_ends(s)) > 0.9 * jump_size;
    if sum(t_90_where) > 0
        range_where = 1:length(t_90_where);
        range_where = range_where(t_90_where);
%         y_where = y(range_starts(s):range_ends(s));
        t_90_slowest = max(t_90_slowest, range_where(1));
    else
        disp('STEP RESPONSE TOO WEAK - 90\% of response not reached')
    end
end

% t_90_average = t_90_average / length(range_starts);

overshoot_average_percentage = 100 * (maximal_overshoot / jump_size);

M_p = overshoot_average_percentage;
t_90 = t_90_slowest * dt;
end