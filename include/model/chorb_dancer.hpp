#ifndef CHORB_DANCER_HPP_22062020
#define CHORB_DANCER_HPP_22062020

#include <string>

class ChorbDancer;  /*!< Declaration of class ChorbDancer. */

//!  A ChorbDancer class.
class ChorbDancer {
 private:

  //!  A private string variable 
  /*!
       Nickname of the dancer.
  */
  std::string nickname;

  //!  A private pointer variable.
  /*!
       Pointer variable points to the left dancer.
  */
  ChorbDancer* leftDancer{nullptr};

  /**
   * @brief Private declaration of boolean function that returns true if the left dancer has been grabbed. Otherwise returns false.
   * 
   */
  bool grabbedLeftDancer{false}; 

  //!  A private pointer variable.
  /*!
       Pointer variable points to the right dancer.
  */
  ChorbDancer* rightDancer{nullptr}; 

  /**
   * @brief Private declaration of boolean function that returns true if the right dancer has been grabbed. Otherwise returns false. 
   * 
   */
  bool grabbedRightDancer{false};

 public:
  ChorbDancer() = default; /*!< Public declaration of the default constructor. */
  explicit ChorbDancer(const std::string& nickname); /*!< Public declaration of the parameterized constructor. */

 /**
  * @brief Public declaration of the boolean function, that returns true if the dancer has grabbed left dancer. Otherwise returns false.
  *  The function does not throw exception.
  * 
  * @return true 
  * @return false 
  */
  bool hasGrabbedLeftDancer() const noexcept;

  /**
   * @brief Public declaration of the function that grabs the left dancer.
   * 
   */
  void grabLeftDancer();

  /**
   * @brief Public declaration of the function that releases left dancer.
   * 
   */
  void releaseLeftDancer();

  /**
   * @brief Public declaration of the function that receives as an input pointer to the chorb dancer
   *  and sets left dancer object.
   * 
   * @param dancer 
   */
  void setLeftDancer(ChorbDancer* dancer);

  /**
   * @brief Public declaration of the function, that gets the left dancer object.
   * 
   * @return const ChorbDancer* 
   */
  const ChorbDancer* getLeftDancer() const;

  /**
   * @brief Public declaration of the boolean function, that returns true if the right dancer has grabbed. 
   *  Otherwise returns false. The function does not throw exception.
   * 
   * @return true 
   * @return false 
   */
  bool hasGrabbedRightDancer() const noexcept;

  /**
   * @brief Public declaration of the boolean function that grabs right dancer.
   * 
   */
  void grabRightDancer();
  /**
   * @brief Public declaration of the function that releases right dancer.
   * 
   */
  void releaseRightDancer(); 
  /**
   * @brief Public declaration of the function that receives as an input pointer to chorb dancer
   *  and sets the right dancer object.
   * 
   * @param dancer 
   */
  void setRightDancer(ChorbDancer* dancer); 
  /**
   * @brief Public declaration of the function that gets the right dancer object.
   * 
   * @return const ChorbDancer* 
   */
  const ChorbDancer* getRightDancer() const; 

  /**
   * @brief Public declaration of the function that gets the nickname object.
   *  The function does not throw exception.
   * 
   * @return std::string 
   */
  std::string getNickname() const noexcept; 
};

#endif
