#ifndef AOC2021_DAILY_TASK_21_H
#define AOC2021_DAILY_TASK_21_H

#include <DailyTask/DailyTask.h>

struct DeterministicDice
{
  int result;

  DeterministicDice() : result(0)
  {
  }

  int roll()
  {
    result++;
    result = result > 100 ? 1 : result;
    return result;
  }
};

struct Game
{
  struct GameHasher
  {
    std::size_t operator()(const Game& g) const
    {
      return static_cast<size_t>(g.player1_pos
      | (g.player1_score << 4)
      | (g.player2_pos << 9)
      | (g.player2_score << 13)
      | (g.player1_last_played << 18));
    }
  };

  int player1_pos;
  int player2_pos;
  int player1_score;
  int player2_score;

  int player1_remaining_rolls;
  int player2_remaining_rolls;
  long turn_count;
  long roll_count;

  bool player1_last_played;

  DeterministicDice dice;

  Game(int pl1_pos, int pl2_pos): player1_pos(pl1_pos), player2_pos(pl2_pos)
  {
    player1_last_played = false;
    player1_score = 0;
    player2_score = 0;
    turn_count = 0;
    roll_count = 0;
    player1_remaining_rolls = 3;
    player2_remaining_rolls = 3;
  }

  bool operator==(const Game &other) const
  { return (player1_pos == other.player1_pos
            && player2_pos == other.player2_pos
            && player1_score == other.player1_score
            && player2_score == other.player2_score
            && player1_last_played == other.player1_last_played);
  }

  void playTurn()
  {
    if (player1_last_played)
    {
      while (player2_remaining_rolls > 0)
      {
        player2_remaining_rolls--;
        player2_pos += dice.roll();
        roll_count++;
        player2_pos = (player2_pos - 1) % 10 + 1;
      }
      player2_remaining_rolls = 3;
      player2_score += player2_pos;
      player1_last_played = false;
    }
    else
    {
      while (player1_remaining_rolls > 0)
      {
        player1_remaining_rolls--;
        player1_pos += dice.roll();
        roll_count++;
        player1_pos = (player1_pos - 1) % 10 + 1;
      }
      player1_remaining_rolls = 3;
      player1_score += player1_pos;
      player1_last_played = true;
    }
    turn_count++;
  }

  void playGame(const int final_score)
  {
    if (player1_score >= final_score || player2_score >= final_score) return;
    playTurn();
    playGame(final_score);
  }

  std::vector<Game> getNextDiracGameStates() const
  {
    std::vector<Game> states;

    for (int i = 1; i <= 3; i++)
    {
      for (int j = 1; j <= 3; j++)
      {
        for (int k = 1; k <= 3; k++)
        {
          int new_pos = player1_last_played ? player2_pos : player1_pos;
          new_pos += i + j + k;
          new_pos = (new_pos - 1) % 10 + 1;
          int new_score = player1_last_played ? player2_score + new_pos : player1_score + new_pos;

          if (player1_last_played)
          {
            Game next_game_state(player1_pos, new_pos);
            next_game_state.player1_score = player1_score;
            next_game_state.player2_score = new_score;
            next_game_state.player1_last_played = false;
            states.push_back(next_game_state);
          }
          else
          {
            Game next_game_state(new_pos, player2_pos);
            next_game_state.player1_score = new_score;
            next_game_state.player2_score = player2_score;
            next_game_state.player1_last_played = true;
            states.push_back(next_game_state);
          }
        }
      }
    }
    return states;
  }
};


class DailyTask21 : DailyTask {
public:
  DailyTask21(std::string task_name) : DailyTask(task_name){};

  virtual void part1();
  virtual void part2();
};

#endif // AOC2021_DAILY_TASK_21_H
