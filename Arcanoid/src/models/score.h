#pragma once
class Score
{
public:
	Score(int record_score);

	int get_current_score();
	void set_current_score(int current_score);

	int get_record_score();
	void set_record_score(int record_score);

	void reset(int record_score);
private:
	int current_score = 0;
	int record_score;
};

