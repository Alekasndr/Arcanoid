#include "score.h"

Score::Score(int record_score)
{
	this->record_score = record_score;
}

int Score::get_current_score()
{
	return current_score;
}

void Score::set_current_score(int current_score)
{
	this->current_score = current_score;
}

int Score::get_record_score()
{
	return record_score;
}

void Score::set_record_score(int record_score)
{
	this->record_score = record_score;
}

void Score::reset(int record_score)
{
	this->record_score = record_score;
	this->current_score = 0;
}
