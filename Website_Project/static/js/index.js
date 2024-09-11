
// Given an empty app object, initializes it filling its attributes,
// creates a Vue instance, and then initializes the Vue instance.
let init = function () {

    var check_meow = {};
    
    // the code below starts the corrected code needed for the meow 
    check_meow.data = {

        selectedID_meow: [],
    // the code below starts the corrected code needed for the meow 

        findFirst_Next: [],
    // the code below starts the corrected code needed for the meow 


        // Complete as you see fit.
        findOption_check: false,

        

        
        selectedFeedOption: 0,
            // the code below starts the corrected code needed for the meow 

        changing_thecorrseponding: [],

    // the code below starts the corrected code needed for the meow 

        selectedFeedOption: null,
        
    };
    
    check_meow.enumerate = function (a) {
        // This adds an _idx field to each element of the array.
        let k = 0;
        a.map((e) => {e._idx = k++;});
        return a;
    };    

    // This contains all the methods.
    check_meow.methods = {
        // Complete as you see fit.

        newApplication: async () => {
            if (check_meow.data.findOption_check) {
              return;
            }
            //axios.get("../get_users").then(function(b) {
  //const followedUsers = b.data.users.filter(user => self.vue.followers.hasOwnProperty(user.id));
  //const unfollowedUsers = b.data.users.filter(user => !self.vue.followers.hasOwnProperty(user.id));
  
 // self.vue.users = followedUsers.concat(unfollowedUsers);
  //moves the users all over
  //self.data.all_users = self.vue.users.slice(); 
  // this part below makes limits so it won't exceed
  //self.vue.users = self.vue.users.slice(0, 10); 
  
  //self.vue.users.forEach(function(user) {
    //self.data.users_as_dict[user.id] = user.username;
          //this will check the data and make sure it is correct with the correct setting
            check_meow.data.findOption_check = true;
            console.log('make sure search is new');
          //this will check the response and make sure it is correct
            const response = await axios.get(get_users_url);
        //this will check the users and make sure it is correct
            const users = response.data.users;
          
            check_meow.data.selectedID_meow = users;
            check_meow.data.findFirst_Next = [...users];
          
            check_meow.data.findOption_check = false;
          },

        selectFeedOption: async (optionIndex, forceRefresh = false) => {
            const shouldRefresh = optionIndex !== check_meow.data.selectedFeedOption || forceRefresh;
          //axios.get("../get_users").then(function(b) {
  //const followedUsers = b.data.users.filter(user => self.vue.followers.hasOwnProperty(user.id));
  //const unfollowedUsers = b.data.users.filter(user => !self.vue.followers.hasOwnProperty(user.id));
  
 // self.vue.users = followedUsers.concat(unfollowedUsers);
  //moves the users all over
  //self.data.all_users = self.vue.users.slice(); 
  // this part below makes limits so it won't exceed
  //self.vue.users = self.vue.users.slice(0, 10); 
  
  //self.vue.users.forEach(function(user) {
    //self.data.users_as_dict[user.id] = user.username;
            if (shouldRefresh) {
              check_meow.data.selectedFeedOption = optionIndex;
              //check for the correct methods 
              await check_meow.methods.figureOutArea();
            }
          },


        
        
        makeAresponse: async (text) => {
            if (check_meow.data.findOption_check || check_meow.data.selectedID_meow === null) {
              return;
            }
            //this checks for a check for response
          
            const filtered = check_meow.data.selectedID_meow.filter(user => user.username.includes(text));
          
            check_meow.data.findFirst_Next.splice(0);
            //this checks for a check for response
            check_meow.data.findFirst_Next.push(...filtered);
          //this checks for a check for response
            return filtered;
            //this checks for a check for response
          },
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////done


        
        
        figureOutArea: async () => {
            check_meow.data.changing_thecorrseponding.splice(0, check_meow.data.changing_thecorrseponding.length);
            //check for the area of the issue
            const params = {
              feed_type: check_meow.data.selectedFeedOption,
              //check for the area of the issue
              reply_source: check_meow.data.selectedFeedOption?.id
            };
          
            let result;
            //check for the area of the issue
          
            try {
              result = await axios.get(get_feed_url, { params });
            } catch (error) {
                //check for the area of the issue
              console.error('there was an error here', error);
              return;
            }
          //axios.get("../get_users").then(function(b) {
  //const followedUsers = b.data.users.filter(user => self.vue.followers.hasOwnProperty(user.id));
  //const unfollowedUsers = b.data.users.filter(user => !self.vue.followers.hasOwnProperty(user.id));
  
 // self.vue.users = followedUsers.concat(unfollowedUsers);
  //moves the users all over
  //self.data.all_users = self.vue.users.slice(); 
  // this part below makes limits so it won't exceed
  //self.vue.users = self.vue.users.slice(0, 10); 
  
  //self.vue.users.forEach(function(user) {
    //self.data.users_as_dict[user.id] = user.username;
            const changing_thecorrseponding = result.data.changing_thecorrseponding.map(meow => {
              meow.timestamp = Sugar.Date(meow.timestamp + "Z").relative();
              return meow;
              //check for the area of the issue
            });
          
            check_meow.data.changing_thecorrseponding.push(...changing_thecorrseponding);
          },


        next_userfoll: async (id, bool) => {
            const payload = {
                //find the next list for the responses
              id: id,
              //find the next list for the responses
              following: bool
            };
            //axios.get("../get_users").then(function(b) {
  //const followedUsers = b.data.users.filter(user => self.vue.followers.hasOwnProperty(user.id));
  //const unfollowedUsers = b.data.users.filter(user => !self.vue.followers.hasOwnProperty(user.id));
  
 // self.vue.users = followedUsers.concat(unfollowedUsers);
  //moves the users all over
  //self.data.all_users = self.vue.users.slice(); 
  // this part below makes limits so it won't exceed
  //self.vue.users = self.vue.users.slice(0, 10); 
  
  //self.vue.users.forEach(function(user) {
    //self.data.users_as_dict[user.id] = user.username;
          
            const response = await axios.post(set_follow_url, payload);
          //find the next list for the responses
            const following = response.data.following;
          
            const userIndex = check_meow.data.selectedID_meow.findIndex(user => user.id === id);
            if (userIndex !== -1) {
                //find the next list for the responses
              check_meow.data.selectedID_meow[userIndex].following = following;
            }
          },
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        

        postMeow: async (text, selectedFeedOption) => {
            let response;
            //check for the next post 
            const postData = { content: text };
          
            if (selectedFeedOption === undefined) {
              response = await axios.post(post_meow_url, postData);
              //check for the correct methods 
              check_meow.methods.figureOutArea();
            } else {

                //check accordingly
              const replyResponse = await axios.post(set_reply_url, {
                findMain: selectedFeedOption.id,
                findNextResponse: response.data.id,
                
                theyreply: true
              });
          //axios.get("../get_users").then(function(b) {
  //const followedUsers = b.data.users.filter(user => self.vue.followers.hasOwnProperty(user.id));
  //const unfollowedUsers = b.data.users.filter(user => !self.vue.followers.hasOwnProperty(user.id));
  
 // self.vue.users = followedUsers.concat(unfollowedUsers);
  //moves the users all over
  //self.data.all_users = self.vue.users.slice(); 
  // this part below makes limits so it won't exceed
  //self.vue.users = self.vue.users.slice(0, 10); 
  
  //self.vue.users.forEach(function(user) {
    //self.data.users_as_dict[user.id] = user.username;
              const replyId = replyResponse.data.id;
          
              const params = {
                feed_type: check_meow.data.selectedFeedOption,
                reply_source: selectedFeedOption.id
              };
          
              const result = await axios.get(get_feed_url, { params });
              check_meow.data.changing_thecorrseponding = result.data.changing_thecorrseponding.map(meow => {
                meow.timestamp = Sugar.Date(meow.timestamp + "Z").relative();
                return meow;
              });
            }
          },


        
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        
        enterReplyMode: (meow) => {
            check_meow.data.selectedFeedOption = meow;
          
            if (check_meow.data.selectedFeedOption !== 3) {
              check_meow.methods.selectFeedOption(3, true);
            }
        }
    };

//check for the correct methods 
    check_meow.methods.figureOutArea();


//check for the correct methods 
    check_meow.methods.newApplication();

    

    // This creates the Vue instance.
    check_meow.vue = new Vue({
        el: "#vue-target",
        data: check_meow.data,
        methods: check_meow.methods
    });

    // Put here any initialization code.

    return check_meow;
};

// This takes the (empty) app object, and initializes it,
// putting all the code in it. 
var app = init();
