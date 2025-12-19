import std::math;

fn uint edit_distance(String t1, String t2) => @pool() {
	if (t2.len > t1.len) {
		@swap(t1, t2);
	}
	uint[] rows = mem::talloc_array(uint, 2 * (t2.len + 1));
	usz r_cur = 0;
	usz r_prev = t2.len + 1;

	for (uint j = 0; j <= t2.len; j++) {
		rows[r_cur + j] = j;
	}
	for (uint i = 1; i <= t1.len; i++) {
		@swap(r_cur, r_prev);
		rows[r_cur + 0] = i;
		for (uint j = 1; j <= t2.len; j++) {
			if (t1[i-1] == t2[j-1]) {
				rows[r_cur + j] = rows[r_prev + j - 1];
			} else {
				rows[r_cur + j] = math::min(
					rows[r_prev + j - 1] + 1,
					rows[r_prev + j] + 1,
					rows[r_cur + j - 1] + 1,
				);
			}
		}
	}
	return rows[r_cur + t2.len];
}

import std::io;
fn int main(String[] args) {
	if (args.len != 3) {
		io::eprintn("You need to pass exactly 2 arguments");
		return 1;
	}
	io::printfn("Edit distance: %d", edit_distance(args[1], args[2]));
	return 0;
}
